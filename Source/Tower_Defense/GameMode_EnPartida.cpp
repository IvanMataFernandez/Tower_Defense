// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode_EnPartida.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonReader.h"
#include "ZonaSpawnRobot.h"
#include "ConstructoraDeBlueprints.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"




/*

    TODO:

        Implementar musica (probablemente requiera crear una clase c++ para ambient sound)
        implementar que cuando 50% del value muera spawnee la siguiente oleada
        Crear logica para handlear win con


        el json level1 tiene la estructura de como deben indicarse los niveles




*/



// Called when the game starts or when spawned
void AGameMode_EnPartida::BeginPlay()
{
	Super::BeginPlay();
    this->OleadaActual = -1; // Las oleadas van como un iterador, 0 based indexing. -1 quiere decir que no está apuntando a ninguna oleada
    this->ZonaSpawn = Cast<AZonaSpawnRobot>(UGameplayStatics::GetActorOfClass(GetWorld(), AZonaSpawnRobot::StaticClass()));

    if (this->ZonaSpawn) {
        this->CargarNivel(1);
        this->EmpezarCargaDeSiguienteOleada();
    } else {
        UE_LOG(LogTemp, Error, TEXT("No hay zona de spawn"));
    }
           

}



void AGameMode_EnPartida::EmpezarCargaDeSiguienteOleada() {
    GetWorld()->GetTimerManager().SetTimer(this->TimerParaOleadas, this, &AGameMode_EnPartida::CargarDatosOleada, this->HastaSiguienteOleada, false);               
}

void AGameMode_EnPartida::CargarDatosOleada() {


    this->OleadaActual++; // Nueva oleada

    TSharedPtr<FJsonObject> DatosOleadaActual = this->OleadasJson[this->OleadaActual]->AsObject();


    this->PesoRestante = DatosOleadaActual->GetIntegerField(TEXT("Peso"));
    this->TiempoEntreSpawn = DatosOleadaActual->GetNumberField(TEXT("tiempoEntreSpawn"));
    this->HastaSiguienteOleada = DatosOleadaActual->GetNumberField(TEXT("tiempoSiguienteOleada"));

    TArray<TSharedPtr<FJsonValue>> ListaProbabilidades =  DatosOleadaActual->GetArrayField(TEXT("probabilidades"));
    float ProbabilidadAcumulada = 0.f;

    for (TSharedPtr< FJsonValue>& Probabilidad : ListaProbabilidades) {
            ProbabilidadAcumulada = ProbabilidadAcumulada + Probabilidad->AsNumber();         
            this->ProbabilidadesRobotAcumuladas.Add(ProbabilidadAcumulada);
    }


    this->PesosRobotActual = this->PesosRobot;
    this->IDsRobotActual = this->IDsRobot;



    this->EmpezarCargaDeSiguienteOleada(); // Ya se han cargado los datos de esta oleada, programar la siguiente



    if (DatosOleadaActual->GetBoolField(TEXT("oleadaGrande"))) {
        // Se aproxima FLAG de robots (oleada grande), esperar unos 5 segundos para TODO:  mostrar cosas por UI y cambiar la música
        GetWorld()->GetTimerManager().SetTimer(this->TimerParaSpawnRobot, this, &AGameMode_EnPartida::SpawnearRobot, 5.f, false);               



    } else {
        // Spawnear YA
        this->SpawnearRobot();

    }


}

void AGameMode_EnPartida::SpawnearRobot() {

    // Toca spawnear un enemigo

    float Random = FMath::FRand();
    int Pos = 0;
    bool Sel = false;
    bool Val = false;

    while (!Sel) {

        // Encontrar donde cae el random

        Pos = 0;
        while (Random >= this->ProbabilidadesRobotAcumuladas[Pos]) {
            Pos++;
        }

        // Pos es el bot elegido, ver si cabe en la oleada

        if (this->PesosRobotActual[Pos] <= this->PesoRestante) {

            // Cabe, se elige Pos como el bot a spawnear

            Sel = true;
            Val = true;

        } else if (this->PesosRobotActual.Num() != 1) { // Queremos eliminar el bot de la lista si no lo podemos permitir, pero si solo queda 1 en la lista eso es que no podemos spawnear mas

            // No cabe, se elimina el bot de la lista de spawneables porque no lo vamos a poder permitir de nuevo para el resto de la oleada actual

            float ProbabilidadAEliminar;

            if (Pos == 0) {
                ProbabilidadAEliminar = this->ProbabilidadesRobotAcumuladas[0];
            } else {
                ProbabilidadAEliminar = this->ProbabilidadesRobotAcumuladas[Pos] - this->ProbabilidadesRobotAcumuladas[Pos-1];
            }

            this->PesosRobotActual.RemoveAt(Pos);
            this->ProbabilidadesRobotAcumuladas.RemoveAt(Pos);
            this->IDsRobotActual.RemoveAt(Pos);

            for (int i = 0; i != ProbabilidadesRobotAcumuladas.Num(); i++) {
                this->ProbabilidadesRobotAcumuladas[i] += ProbabilidadAEliminar/ProbabilidadesRobotAcumuladas.Num();
            }



        } else {
            // NO SE PUEDE ELEGIR, todos los robots cuestan más que el budget de oleada actual
            Sel = true;
            Val = false;
        }




    }

    if (Val) { 
        // SPAWN si se puedo elegir bot


        UE_LOG(LogTemp, Warning, TEXT("SPAWN"));
        this->ZonaSpawn->SpawnearRobot(this->IDsRobotActual[Pos], FMath::RandRange(0,4)); // Spawnear el robot en una fila al azar
            UE_LOG(LogTemp, Warning, TEXT("%d"), this->PesosRobotActual[Pos]);

        this->PesoRestante = this->PesoRestante - this->PesosRobotActual[Pos]; // Restar al budget de oleada

        if (this->PesoRestante != 0) {
            // Si queda budget, llamar a esta funcion de nuevo tras el cooldown de spawnear un robot
            GetWorld()->GetTimerManager().SetTimer(this->TimerParaSpawnRobot, this, &AGameMode_EnPartida::SpawnearRobot, this->TiempoEntreSpawn , false);
                    UE_LOG(LogTemp, Warning, TEXT("No more budget"));

        } 
    } else {
                UE_LOG(LogTemp, Warning, TEXT("Couldnt spaewn"));

    }
 






}


void AGameMode_EnPartida::CargarNivel(int Nivel) {

    // Resetear variables


    // Cargar JSON

    FString NivelString = FString::Printf(TEXT("%d"), Nivel);
    FString FilePath = FPaths::ProjectContentDir() + FString(TEXT("/Niveles/NivelesData/nivel")) + NivelString + FString(TEXT(".json"));

    FString Contenido;
    if (FFileHelper::LoadFileToString(Contenido, *FilePath)) {
        TSharedPtr<FJsonObject> JsonNivel;


        if (FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Contenido), JsonNivel)) {
            UE_LOG(LogTemp, Warning, TEXT("Success!"));
            

            // Obtener los campos de los datos de la oleada

            this->OleadasJson = JsonNivel->GetArrayField(TEXT("oleadas"));

            // Obtener el header json con los datos principales del nivel

            JsonNivel = JsonNivel->GetObjectField(TEXT("header"));
            
            this->HastaSiguienteOleada = JsonNivel->GetNumberField(TEXT("tiempoSinEnemigos"));

            this->OleadasTotales = JsonNivel->GetIntegerField(TEXT("oleadas"));

           
            TArray<TSharedPtr<FJsonValue>> ListaIDsRobots =  JsonNivel->GetArrayField(TEXT("robotsPermitidos"));

            for (TSharedPtr< FJsonValue>& ValorId : ListaIDsRobots) {
                this->IDsRobot.Add(ValorId->AsNumber());
            }


            // Se han obtenido los robots spawneables, obtener sus pesos ahora

            for (int Id : this->IDsRobot) {
                PesosRobot.Add(ConstructoraDeBlueprints::GetConstructoraDeBlueprints()->GetPesoDeRobot(Id));  
            }


        } else {
            UE_LOG(LogTemp, Warning, TEXT("ERROR"));

        }



    } else {
        UE_LOG(LogTemp, Warning, TEXT("ERROR"));

    }


}

