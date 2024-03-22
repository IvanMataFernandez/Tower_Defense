// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode_EnPartida.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonReader.h"
#include "ZonaSpawnRobot.h"
#include "Musica_EnPartida.h"
#include "ConstructoraDeBlueprints.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"




/*




        el json level1 tiene la estructura de como deben indicarse los niveles




*/



// Called when the game starts or when spawned
void AGameMode_EnPartida::BeginPlay()
{
	Super::BeginPlay();
    this->OleadaActual = -1; // Las oleadas van como un iterador, 0 based indexing. -1 quiere decir que no está apuntando a ninguna oleada
    this->SeQuiereSpawnearLaSiguienteOleada = false;
    this->ZonaSpawn = Cast<AZonaSpawnRobot>(UGameplayStatics::GetActorOfClass(GetWorld(), AZonaSpawnRobot::StaticClass()));
    this->ReproductorEnPartida = Cast<AMusica_EnPartida>(UGameplayStatics::GetActorOfClass(GetWorld(), AMusica_EnPartida::StaticClass()));

    if (this->ZonaSpawn && ReproductorEnPartida) {

        this->PesoRobotsVivo = 0;


        this->ReproductorEnPartida->Tocar(0);

        this->CargarNivel(1);
        this->EmpezarCargaDeSiguienteOleada();

    } else {
        UE_LOG(LogTemp, Error, TEXT("No hay zona de spawn / reproductor"));
    }



           

}

void AGameMode_EnPartida::ProcesarMuerteDeRobot(int PesoDeRobot) {


    // Restar el peso del robot de los robots vivos restantes
    this->PesoRobotsVivo = PesoRobotsVivo - PesoDeRobot;

    if (this->OleadaActual != this->OleadasTotales-1) { // Determinar si es la ultima oleada o no

        // Si no lo es, determinar si hemos hitteado el threshold para spawnear la siguiente oleada antes (no se pueden adelantar las oleadas gordas)

        if (!this->SeAproximaOrdaGrande && this->PesoTargetParaSiguienteOleada >= this->PesoRobotsVivo) {

            // Se quiere Adelantar la oleada, para ello mirar si la oleada anterior todavía está spawneando (solo puede ocurrir si el jugador tiene un montón de DPS)


            if (GetWorld()->GetTimerManager().IsTimerActive(this->TimerParaSpawnRobot)) {

                // La oleada anterior está spawneando, marcar un flag para que cuando acabe de spawnear inmediatamente empiece con esta

                this->SeQuiereSpawnearLaSiguienteOleada = true; 
            
            } else {

                // Hay via libre, cancelar el timer del spawn de la siguiente oleada para hacerlo AHORA MISMO
                GetWorld()->GetTimerManager().ClearTimer(this->TimerParaOleadas);
                this->CargarDatosOleada();
            }

        // Aunque no se puedan adelantar oleadas gordas, no tiene sentido quedarse esperando si no hay bots vivos (y no hay spawneando nuevos).
        // en ese caso programos para que el aviso de oleada salte en 3 segundos

        } else if (this->PesoRobotsVivo == 0 && !GetWorld()->GetTimerManager().IsTimerActive(this->TimerParaSpawnRobot)) {
            GetWorld()->GetTimerManager().SetTimer(this->TimerParaOleadas, this, &AGameMode_EnPartida::CargarDatosOleada, 3.f, false);               

        }

    } else if (this->PesoRobotsVivo == 0) { // Si es la última oleada, comprobar si hay robots vivos para dar la victoria al jugador o no

         // TODO: Crear logica winscreen etc
        UE_LOG(LogTemp, Warning, TEXT("YOU WIN!"));
        
    }





}


void AGameMode_EnPartida::EmpezarCargaDeSiguienteOleada() {

    if (this->OleadaActual != this->OleadasTotales-1) { 
        GetWorld()->GetTimerManager().SetTimer(this->TimerParaOleadas, this, &AGameMode_EnPartida::CargarDatosOleada, this->HastaSiguienteOleada, false);               
    }
}

void AGameMode_EnPartida::CargarDatosOleada() {


    this->OleadaActual++; // Nueva oleada

    // Recopilar datos de oleada actual

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
    this->PesoTargetParaSiguienteOleada = this->PesoRobotsVivo / 3 + this->PesoRestante / 2; // Spawnear siguiente orda antes si solo queda la mitad del peso de esta orda + 
                                                                                             // el tercio de los robots que ya habían presentes previa a esta

    // Recopilar datos de siguiente oleada

    if (this->OleadaActual != this->OleadasTotales-1) {
        TSharedPtr<FJsonObject> DatosOleadaSiguiente = this->OleadasJson[this->OleadaActual+1]->AsObject();
        this->SeAproximaOrdaGrande = DatosOleadaSiguiente->GetBoolField(TEXT("oleadaGrande")); 
    }



    // Ya se han cargado los datos de esta oleada, programar la siguiente


    this->EmpezarCargaDeSiguienteOleada(); 


    // Ya tenemos los datos de la oleada, empezar a handlear logica de spawnear enemigos


    if (DatosOleadaActual->GetBoolField(TEXT("oleadaGrande"))) {
 

        this->SeAproximaOrdaGrande = false; // No hay dos ordas grandes seguidas

        // Se aproxima FLAG de robots (oleada grande), esperar unos 5 segundos para TODO:  mostrar cosas por UI
        GetWorld()->GetTimerManager().SetTimer(this->TimerParaSpawnRobot, this, &AGameMode_EnPartida::SpawnearRobot, 5.f, false);   


        if (this->OleadaActual != this->OleadasTotales-1) {
            // No ultima orda
            this->ReproductorEnPartida->Tocar(1);
        }  else {
            // Ultima orda
            this->ReproductorEnPartida->Tocar(2);
        }          



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

        // TODO: Considerar aumentar odds para filas que no spawnearon hace tiempo y disminuir para las que acaban de spawnear

        this->ZonaSpawn->SpawnearRobot(this->IDsRobotActual[Pos] ,FMath::RandRange(0,4)); // Spawnear el robot en una fila al azar
            UE_LOG(LogTemp, Warning, TEXT("%d"), this->PesosRobotActual[Pos]);

        this->PesoRestante = this->PesoRestante - this->PesosRobotActual[Pos]; // Restar al budget de oleada

        this->PesoRobotsVivo = this->PesoRobotsVivo + this->PesosRobotActual[Pos]; // Contabilizar el peso de robot en el counter


        if (this->PesoRestante != 0) {
            // Si queda budget, llamar a esta funcion de nuevo tras el cooldown de spawnear un robot
            GetWorld()->GetTimerManager().SetTimer(this->TimerParaSpawnRobot, this, &AGameMode_EnPartida::SpawnearRobot, this->TiempoEntreSpawn , false);

        } else if (this->SeQuiereSpawnearLaSiguienteOleada) {
            // Si no queda budget pero se habia triggeado el flag de querer spawnear la siguiente oleada YA, como justo hemos acabdo de spawnear esta, crear la siguiente.

            this->SeQuiereSpawnearLaSiguienteOleada = false;
            this->CargarDatosOleada();

        }
    } 
 


//  LogAudioCaptureCore: Display: No Audio Capture implementations found. Audio input will be silent.



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

