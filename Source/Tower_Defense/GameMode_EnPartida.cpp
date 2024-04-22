// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode_EnPartida.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonReader.h"
#include "ZonaSpawnRobot.h"
#include "Musica_EnPartida.h"
#include "ConstructoraDeBlueprints.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "MandoDeJugador_EnPartida.h"
#include "ZonaSpawnRobotPreview.h"
#include "Robot.h"
#include "PlayerPawn_EnPartida.h"
#include "Proyectil.h"
#include "Guardador.h"
#include "Torre.h"


/*




        el json level1 tiene la estructura de como deben indicarse los niveles


        El juego comprueba si tras matar sufucientes bots para spawnear la siguiente oleada si la actual todavía esta spawneando
        El juejo NO comprueba esto con los timers básicos de spawnear la siguiente (hacer que los timers tengan como mínimo de tiempo,
        lo que tarden en spawnear el maximo numero de bots y 6 segundos extra si es una gran oleada)


*/



// Called when the game starts or when spawned
void AGameMode_EnPartida::BeginPlay()
{
	Super::BeginPlay();





   
    this->ZonaSpawn = Cast<AZonaSpawnRobot>(UGameplayStatics::GetActorOfClass(GetWorld(), AZonaSpawnRobot::StaticClass()));
    this->ReproductorEnPartida = Cast<AMusica_EnPartida>(UGameplayStatics::GetActorOfClass(GetWorld(), AMusica_EnPartida::StaticClass()));
    this->ZonaSpawnPreview = Cast<AZonaSpawnRobotPreview>(UGameplayStatics::GetActorOfClass(GetWorld(), AZonaSpawnRobotPreview::StaticClass()));
    this->Camara = Cast<APlayerPawn_EnPartida>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());

    if (this->ZonaSpawn && this->ReproductorEnPartida && this->ZonaSpawnPreview ) {

        this->ReproductorEnPartida->Tocar(3);



        UGuardador* Guardado = Cast<UGuardador>(UGameplayStatics::LoadGameFromSlot(TEXT("save"), 0));

        
        
        // TODO: Quitar esto en version final, por ahora fallsafe a lv 1 si no hay save file (aunque deberia haberla pq main menu la crea)

        if (Guardado) {
            this->NivelActual = Guardado->Nivel;

        } else {
            this->NivelActual = 1;
        }



        // Cargar info del nivel actual

        this->CargarNivel(this->NivelActual);

        // Esperar medio segundo para empezar a mover la camara

        FTimerHandle Espera;
        GetWorld()->GetTimerManager().SetTimer(Espera, this->Camara, &APlayerPawn_EnPartida::MoverCamASeleccion, 0.5f, false);       


        // Cuando la camara acabe de moverse, se ejecuta:  this->EmpezarSeleccionDeTorres();




    } else {
        UE_LOG(LogTemp, Error, TEXT("No hay zonas de spawn / reproductor"));
    }



           

}


void AGameMode_EnPartida::SpawnearRobotsPreview() {

    int PesoMax = 0;
    float RobotsTotalesPorTipoF = (FMath::RandRange(8,12) + 4 * (this->IDsRobot.Num()-1)) / this->IDsRobot.Num() ; // Spawnear en preview. Contra más tipos de bots, dar mas peso porque se pierde en redondeos
    int RobotsTotalesPorTipo = FMath::RoundToInt(RobotsTotalesPorTipoF);
    TArray<int> RobotsASpawnear;

    UE_LOG(LogTemp, Display, TEXT("sieze: %d"),this->IDsRobot.Num());
    // Por cada tipo de robot, ver cuantos caben en la preview segun el peso maximo seleccionado

    for (int i = 0; i != IDsRobot.Num(); i++) {
        int ID = this->IDsRobot[i];
        int Peso = this->PesosRobot[i];
        int CantidadRobotASpawnear = FMath::RoundToInt(RobotsTotalesPorTipo * 1.f/Peso); 

        for (int j = 0; j != CantidadRobotASpawnear; j++) {
            RobotsASpawnear.Add(ID);

        }

    }

    // Reordenar el array al azar para dar mas naturalidad a los spawns
    TArray<int> RobotsASpawnearShuffled;

    while (!RobotsASpawnear.IsEmpty()) {

        // Buscar el index a insertar despues
        int Seleccion =  FMath::RandRange(0,RobotsASpawnear.Num()-1);

        // Encontrar el ID
        int IDElegido = RobotsASpawnear[Seleccion];

        // Mover el ultimo elemento de la lista a la posicion de la que se ha cogido el ID y quitar el ultimo elemento de la lista (ahorra tiempo computacional)
        RobotsASpawnear[Seleccion] = RobotsASpawnear[RobotsASpawnear.Num()-1];
        RobotsASpawnear.Pop();

        // Añadirlo a la lista shuffled


        RobotsASpawnearShuffled.Add(IDElegido);


    }

    // Finalmente, spawnear dichos robots

    for (int ID: RobotsASpawnearShuffled) {
        this->ZonaSpawnPreview->SpawnearRobot(ID);
    }



}

void AGameMode_EnPartida::FinSeleccionTorres(TArray<int> IDsTorresElegidas) {


    // Dar al mando del jugador las torres elegidas por la interfaz

    Cast<AMandoDeJugador_EnPartida>(GetWorld()->GetFirstPlayerController())->SetTorresElegidas(IDsTorresElegidas);


    this->Camara->MoverCamAJugar();

    // Tras acabar de mover la cam, se llama a EmpezarJuego()

  

}

void AGameMode_EnPartida::EmpezarSeleccionDeTorres() {



    // Spawnear los bots de preview
    this->SpawnearRobotsPreview();



    // Esperar un par de segundos para que los bots se acerquen antes de dar la opcion al usuario de que elija sus torres
    
    FTimerHandle Espera;
    GetWorld()->GetTimerManager().SetTimer(Espera, this, &AGameMode_EnPartida::CrearInterfazSeleccionDeTorres, 4.5f, false);               


}

void AGameMode_EnPartida::EliminarRobotsPreview() {

    // Quitar los bots de la preview cuando se empieza a jugar porque ya no se ven de todas formas y consumen recursos

    TArray<AActor*> RobotsPreview;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARobot::StaticClass(), RobotsPreview);

    for (AActor* Robot: RobotsPreview) {
        Robot->Destroy();
    }
   
}


void AGameMode_EnPartida::CargarCuentaAtrasParaEmpezarJuego() {

    this->EliminarRobotsPreview();

    this->CrearInterfazDeCuentaAtras();
    this->ReproductorEnPartida->Tocar(4); // Hacer sonar cuenta atrás



    // La interfaz de cuenta atrás se crea y cuando acabe su cue

  //  FTimerHandle EsperarACountDown;
  //  GetWorld()->GetTimerManager().SetTimer(EsperarACountDown, this, &AGameMode_EnPartida::EmpezarJuego, 3.f, false);               

}


void AGameMode_EnPartida::EmpezarJuego() {



    this->PesoRobotsVivo = 0;
    this->OleadaActual = -1; // Las oleadas van como un iterador, 0 based indexing. -1 quiere decir que no está apuntando a ninguna oleada
    this->SeQuiereSpawnearLaSiguienteOleada = false;
    this->VictoriaPosible = false;
    this->CantidadRobotsSpawneados = 0;

    // 5 filas, 5 posiciones en el array de spawns por fila
    this->CantidadRobotsSpawneadosPorLinea.Add(0);
    this->CantidadRobotsSpawneadosPorLinea.Add(0);
    this->CantidadRobotsSpawneadosPorLinea.Add(0);
    this->CantidadRobotsSpawneadosPorLinea.Add(0);
    this->CantidadRobotsSpawneadosPorLinea.Add(0);

    this->ReproductorEnPartida->Tocar(0);
    this->CrearInterfazDePartida();

    this->EmpezarCargaDeSiguienteOleada();

}





void AGameMode_EnPartida::ProcesarMuerteDeRobot(int PesoDeRobot, ARobot* RobotMatado) {


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
        // en ese caso programos para que el aviso de oleada salte en 1 segundo

        } else if (this->PesoRobotsVivo == 0 && this->PesoRestante == 0) {

            GetWorld()->GetTimerManager().ClearTimer(this->TimerParaOleadas);
            GetWorld()->GetTimerManager().SetTimer(this->TimerParaOleadas, this, &AGameMode_EnPartida::CargarDatosOleada, 1.f, false);               

        }

    // Si es la última oleada, comprobar si hay robots vivos para dar la victoria al jugador o no. El flag victoria posible no se triggea hasta que spawnea
    // el primer bot de la oleada final. Los pesos comprueban si hay bots vivos y si quedan por spawnear
    } else if (this->VictoriaPosible && this->PesoRobotsVivo == 0 && this->PesoRestante == 0) { 


        // Si el ultimo bot acaba de morir, dar la victoria al jugador

        this->JugadorGana(RobotMatado);
        
    }





}

void AGameMode_EnPartida::JugadorGana(ARobot* UltimoRobotMatado) {



    // Localizar donde murio el ultimo robot para poner el dropable ahí en UI

    APlayerController* MandoDeJugador = UGameplayStatics::GetPlayerController(GetWorld(), 0); 
    FVector2D PosicionEnPantalla;
    MandoDeJugador->ProjectWorldLocationToScreen(UltimoRobotMatado->GetActorLocation(), PosicionEnPantalla);

    // Comunicar a la UI de lo ocurrido

    this->ComunicarVictoria(this->NivelActual, PosicionEnPantalla.X, PosicionEnPantalla.Y);

   
    // Pausar todas las torres porque no se necesitan ya, también se han bloqueado los botones de la interfaz de donde se pueden poner mas torres
    // para no poder colocar mas tras ganar (en blueprint)

    TArray<AActor*> Torres;
    
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATorre::StaticClass(), Torres);

    for (AActor* Torre : Torres) {

        Cast<AEntidad>(Torre)->PausarEntidad();
    }



}


void AGameMode_EnPartida::ProcesarClickEnRecompensa() {

    // Cuando se hace click en la recompensa, se cambia a musica de victoria y se quita la interfaz de EnPartida (esto ultimo en blueprint)

    this->ReproductorEnPartida->Tocar(7);

}


void AGameMode_EnPartida::AvanzarNivel(int TorreDesbloqueo) {


    // Obtener la save

    UGuardador* Guardado = Cast<UGuardador>(UGameplayStatics::LoadGameFromSlot(TEXT("save"), 0));

    // Decirle a la save que hemos avanzado un nivel y desbloqueado una torre

    Guardado->IDsTorresDesbloqueadas.Add(TorreDesbloqueo); // TODO: Handlear caso en el que no se desbloquea una torre
    Guardado->Nivel = this->NivelActual + 1;
    UGameplayStatics::SaveGameToSlot(Guardado, TEXT("save"), 0);

    // Cargar este nivel de nuevo para que se carge la información del nuevo nivel al que apunta la save ahora
     
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("NivelPrincipal"));
}





void AGameMode_EnPartida::EmpezarCargaDeSiguienteOleada() {

    if (this->OleadaActual != this->OleadasTotales-1) { 
        GetWorld()->GetTimerManager().SetTimer(this->TimerParaOleadas, this, &AGameMode_EnPartida::CargarDatosOleada, this->HastaSiguienteOleada, false);               
    }
}

void AGameMode_EnPartida::CargarDatosOleada() {



    this->OleadaActual++; // Nueva oleada
    UE_LOG(LogTemp, Display, TEXT("Oleada: %d"), OleadaActual);
    UE_LOG(LogTemp, Display, TEXT("Peso: %d"), PesoRobotsVivo);

    // Recopilar datos de oleada actual

    TSharedPtr<FJsonObject> DatosOleadaActual = this->OleadasJson[this->OleadaActual]->AsObject();


    this->PesoRestante = DatosOleadaActual->GetIntegerField(TEXT("Peso"));
    this->TiempoEntreSpawn = DatosOleadaActual->GetNumberField(TEXT("tiempoEntreSpawn"));
    this->HastaSiguienteOleada = DatosOleadaActual->GetNumberField(TEXT("tiempoSiguienteOleada"));




    this->PesoTargetParaSiguienteOleada = this->PesoRobotsVivo / 3 + this->PesoRestante / 2; // Spawnear siguiente orda antes si solo queda la mitad del peso de esta orda + 
                                                                                             // el tercio de los robots que ya habían presentes previa a esta

    // Refrescar listas auxiliares

    this->PesosRobotActual = this->PesosRobot;
    this->IDsRobotActual = this->IDsRobot;
    this->ProbabilidadesRobotAcumuladas.Empty();

    TArray<TSharedPtr<FJsonValue>> ListaProbabilidades =  DatosOleadaActual->GetArrayField(TEXT("probabilidades"));
    float ProbabilidadAcumulada = 0.f;

    for (TSharedPtr< FJsonValue>& Probabilidad : ListaProbabilidades) {
            ProbabilidadAcumulada = ProbabilidadAcumulada + Probabilidad->AsNumber(); 
            this->ProbabilidadesRobotAcumuladas.Add(ProbabilidadAcumulada);

    }



    // Recopilar datos de siguiente oleada

    if (this->OleadaActual != this->OleadasTotales-1) {
        this->SeAproximaOrdaGrande = this->GrandesOleadas.Contains(this->OleadaActual+1);
    }



    // Ya se han cargado los datos de esta oleada, programar la siguiente


    this->EmpezarCargaDeSiguienteOleada(); 


    // Ya tenemos los datos de la oleada, empezar a handlear logica de spawnear enemigos


    if (this->GrandesOleadas.Contains(this->OleadaActual)) {
 


        // Se aproxima FLAG de robots (oleada grande), esperar unos 6 segundos para 
       
        // TODO:  Mostrar cosas por UI

 
        GetWorld()->GetTimerManager().SetTimer(this->TimerParaSpawnRobot, this, &AGameMode_EnPartida::GenerarOleadaGrande, 6.f, false);   


        if (this->OleadaActual != this->OleadasTotales-1) {
            // No ultima orda
            this->ReproductorEnPartida->Tocar(1);
        }  else {
            // Ultima orda
            this->ReproductorEnPartida->Tocar(2);
        }          



    } else {

        // Spawnear la oleada normal ya

        this->GenerarOleada();

    }


}

void AGameMode_EnPartida::GenerarOleada() {

    // Se quiere spawnear una oleada normal


    this->ComunicarAvanceOleadaUI(); // Triggear avance en progress bar
    this->GenerarRobot(); // Empezar los spawns de robots
}



void AGameMode_EnPartida::GenerarOleadaGrande() {


    // Se quiere spawnear una oleada grande

    this->ComunicarAvanceOleadaUI(); // Triggear avance en progress bar

    // Spawnear lider de oleada (tiene coste de peso 1)
    this->SpawnearRobot(-1); 
    
     // Programar el spawn del resto de la oleada
    GetWorld()->GetTimerManager().SetTimer(this->TimerParaSpawnRobot, this, &AGameMode_EnPartida::GenerarRobot, this->TiempoEntreSpawn, false); 


    // Determinar si esta gran oleada es la ultima, se debe tomar la decision tras spawnear el primer bot para que no sea posible que el juego
    // avance la oleada, no spawnee todavía y se mate el ultimo bot del nivel, haciendo pensar al juego que has ganado

    if (this->OleadaActual == this->OleadasTotales-1) {
        this->VictoriaPosible = true;
    }


}


void AGameMode_EnPartida::GenerarRobot() {

    // Toca spawnear un enemigo, elige QUE bot spawnear

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

         
         
            // TODO: Debug esto por si acaso, pero debería ir. Hace que cuando se quita una probabilidad, se añade a las demas en proporcion de la probabilidad
            //       de cada uno

            float ProbabilidadAEliminar;

            if (Pos == 0) {
                ProbabilidadAEliminar = this->ProbabilidadesRobotAcumuladas[0];
            } else {
                ProbabilidadAEliminar = this->ProbabilidadesRobotAcumuladas[Pos] - this->ProbabilidadesRobotAcumuladas[Pos-1];
            }

            if (ProbabilidadAEliminar <= 0.999f) {
                this->PesosRobotActual.RemoveAt(Pos);
                this->ProbabilidadesRobotAcumuladas.RemoveAt(Pos);
                this->IDsRobotActual.RemoveAt(Pos);


                for (int i = Pos; i != ProbabilidadesRobotAcumuladas.Num(); i++ ) {
                    ProbabilidadesRobotAcumuladas[i] = ProbabilidadesRobotAcumuladas[i] - ProbabilidadAEliminar;
                }

                TArray<float> ReferenciasProbabilidadesAcumuladas; // TArray para poder sacar las probabilidades sin acumular, ya que el otro se va a ir actualizando
                                                                // y se van a mezclar los datos


                ReferenciasProbabilidadesAcumuladas = ProbabilidadesRobotAcumuladas;
                float ProbabilidadBase;
                float ProbabilidadBasePrevia = 0.f;

                for (int i = 0; i != ProbabilidadesRobotAcumuladas.Num(); i++) {

                    if (i == 0) {
                        ProbabilidadBase = ReferenciasProbabilidadesAcumuladas[i];
                    } else {
                        ProbabilidadBase = ReferenciasProbabilidadesAcumuladas[i] - ReferenciasProbabilidadesAcumuladas[i-1];

                    }

                    this->ProbabilidadesRobotAcumuladas[i] = ProbabilidadBasePrevia + ProbabilidadBase + (ProbabilidadBase/(1.f - ProbabilidadAEliminar)) * ProbabilidadAEliminar;
                
                    ProbabilidadBasePrevia = ProbabilidadBase;
                            
                            

                }
            
            } else {
                // NO SE PUEDE ELEGIR, el resto de bots tienen chance 0% de spawnear en esta wave
                Sel = true;
                Val = false;        
            }





        } else {
            // NO SE PUEDE ELEGIR, todos los robots cuestan más que el budget de oleada actual
            Sel = true;
            Val = false;
        }




    }

    if (Val) { 
        // SPAWN si se puedo elegir bot


        this->SpawnearRobot(Pos);



        if (this->PesoRestante != 0) {
            // Si queda budget, llamar a esta funcion de nuevo tras el cooldown de spawnear un robot
            GetWorld()->GetTimerManager().SetTimer(this->TimerParaSpawnRobot, this, &AGameMode_EnPartida::GenerarRobot, this->TiempoEntreSpawn , false);

        } else if (this->SeQuiereSpawnearLaSiguienteOleada) {
            // Si no queda budget pero se habia triggeado el flag de querer spawnear la siguiente oleada YA, como justo hemos acabdo de spawnear esta, crear la siguiente.

            this->SeQuiereSpawnearLaSiguienteOleada = false;

            // Cancelar la programacion de la siguiente oleada para hacerlo YA en su lugar

            GetWorld()->GetTimerManager().ClearTimer(this->TimerParaOleadas);
            this->CargarDatosOleada();

        }
    } 
 





}

void AGameMode_EnPartida::SpawnearRobot(int Pos) {
    

    // Pos indica la posicion del id de robot en el array de robots disponibles del nivel.
    // Por ejemplo, si se permite basico (id = 0) y bomba (id = 8), el array de disponibilidad es [0,8]
    // Si se desea spawnear basico, se usa pos 0, y para bomba pos 1, ya que esos indexan el array de disponibilidad

    int ID;
    int PesoRobot;
    
    
    if (Pos >= 0) {

        // Obtener del array de disponibilidad el identificador del bot a spawnear

        ID = this->IDsRobotActual[Pos];
        PesoRobot = this->PesosRobotActual[Pos];

    } else {

        // El bot lider de oleada no se pone en el array de disponibilidad, se da por sentado que siempre esta disponible pero solo uno por cada oleada grande
        // Por ello, ocupa la pos "-1" del array de disponibilidad

        ID = 1;
        PesoRobot = ConstructoraDeBlueprints::GetConstructoraDeBlueprints()->GetPesoDeRobot(ID);

    }

    this->PesoRobotsVivo = this->PesoRobotsVivo + PesoRobot; // Contabilizar el peso de robot en el counter
    this->PesoRestante = this->PesoRestante - PesoRobot; // Restar al budget de oleada


    // Ya se ha computado el coste del robot, ahora elegir en que linea va a aparecer. Las lineas que han spawneado
    // menos bots tienen mas probabilidad de ser elegidas.



    // Paso 1, obtener la proporcion de spawns por cada fila pero en su inverso. Se da un spawn extra por fila para no tratar con diviones por 0.
    //         se obtiene tambien el total de la suma de los inversos

    TArray<float> ValoresPorFila;
    float Total = 0.f; // Sumatorio de los inversos

    for (int CantidadEnFila : this->CantidadRobotsSpawneadosPorLinea) {
        float ProporcionInversa = (this->CantidadRobotsSpawneados+5)/(CantidadEnFila+1);
        ValoresPorFila.Add(ProporcionInversa);
        Total = Total + ProporcionInversa;
    }

    // Paso 2, computar las probabilidades acumuladas de spawnear en cada fila segun proporcion  inverso / inversoTotal  calculado en el paso 1

    float Acumulado = 0.f; // Probabilidad acumulada hasta ahora

    for (int Fila = 0; Fila != ValoresPorFila.Num(); Fila++) {

        ValoresPorFila[Fila] = Acumulado + ValoresPorFila[Fila] / Total;
        Acumulado = ValoresPorFila[Fila];
    }


    // Paso 3, rollear el random y ver donde cae para poner el robot ahí

    float Random = FMath::FRand(); // Random float  [0, 1)


    int FilaElegida = 0;
    

    while (Random >= ValoresPorFila[FilaElegida]) {
        FilaElegida++;
    }


    // Spawnear el bot con id "ID" en la fila "FilaElegida"

    this->ZonaSpawn->SpawnearRobot(ID ,FilaElegida); 

    // Y actualizar a las variables que trackean los contadores de spawns de robots segun corresponda

    this->CantidadRobotsSpawneados++;
    this->CantidadRobotsSpawneadosPorLinea[FilaElegida] = this->CantidadRobotsSpawneadosPorLinea[FilaElegida] + 1;
}

TArray<int> AGameMode_EnPartida::EncontrarGrandesOleadas() {

    TArray<int> GransOleadas;
    int Num = 0;

    for (TSharedPtr<FJsonValue> Oleada : this->OleadasJson) {

        if (Oleada->AsObject()->GetBoolField(TEXT("oleadaGrande"))) {
            GransOleadas.Add(Num);
        }
        

        Num++;
    }

    return GransOleadas;

}


void AGameMode_EnPartida::CongelarMundoPorDerrota(ARobot* Causante) {


    this->CausanteDerrota = Causante;
    this->ReproductorEnPartida->Tocar(5);
   
    // Parar spawns

    GetWorld()->GetTimerManager().ClearTimer(this->TimerParaOleadas);
    GetWorld()->GetTimerManager().ClearTimer(this->TimerParaSpawnRobot);


    // Quitar interfaz de juego durante game over screen

    this->QuitarInterfaz();



    // Pausar todas las entidades

    TArray<AActor*> Entidades;
    
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEntidad::StaticClass(), Entidades);

    for (AActor* Entidad : Entidades) {

        Cast<AEntidad>(Entidad)->PausarEntidad();
    }



    // Pausar todos los proyectiles

    TArray<AActor*> Proyectiles;

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AProyectil::StaticClass(), Proyectiles);

    for (AActor* Proyectil : Proyectiles) {

        Cast<AProyectil>(Proyectil)->Pausar();
    }


    // Mover la cam a la izquierda para ver el robot que se ha colado

    this->Camara->MoverCamAIzquierda();








}
void AGameMode_EnPartida::FocusearCausanteDerrota() {
    

    // Descongelar al robot causante de la derrota, manteniendo el resto del tablero congelado

    this->CausanteDerrota->DespausarEntidad();

    FTimerHandle TimerParaUI;

    GetWorld()->GetTimerManager().SetTimer(TimerParaUI, this, &AGameMode_EnPartida::FinalizarAnimacionDerrota, 2.f, false); 


}

void AGameMode_EnPartida::FinalizarAnimacionDerrota() {
    this->CausanteDerrota->Destroy();
    
    this->CrearInterfazDeDerrota(); // Llamado por blueprint
    this->ReproductorEnPartida->Tocar(6);



}



void AGameMode_EnPartida::CargarNivel(int Nivel) {

    // Resetear variables


    // Cargar JSON

    FString NivelString = FString::Printf(TEXT("%d"), Nivel);
    FString FilePath = FPaths::ProjectContentDir() + FString(TEXT("/InfoDeJuego/Niveles/nivel")) + NivelString + FString(TEXT(".json"));

    FString Contenido;
    if (FFileHelper::LoadFileToString(Contenido, *FilePath)) {
        TSharedPtr<FJsonObject> JsonNivel;


        if (FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Contenido), JsonNivel)) {
            

            // Obtener los campos de los datos de la oleada

            this->OleadasJson = JsonNivel->GetArrayField(TEXT("oleadas"));

            // Obtener el header json con los datos principales del nivel

            JsonNivel = JsonNivel->GetObjectField(TEXT("header"));
            
            this->HastaSiguienteOleada = JsonNivel->GetNumberField(TEXT("tiempoSinEnemigos"));

            this->OleadasTotales = this->OleadasJson.Num();

           
            TArray<TSharedPtr<FJsonValue>> ListaIDsRobots =  JsonNivel->GetArrayField(TEXT("robotsPermitidos"));
            for (TSharedPtr< FJsonValue>& ValorId : ListaIDsRobots) {
                this->IDsRobot.Add(ValorId->AsNumber());
            }


            // Se han obtenido los robots spawneables, obtener sus pesos ahora

            for (int Id : this->IDsRobot) {
                PesosRobot.Add(ConstructoraDeBlueprints::GetConstructoraDeBlueprints()->GetPesoDeRobot(Id));  
            }


            this->GrandesOleadas = this->EncontrarGrandesOleadas();

 

        } else {
            UE_LOG(LogTemp, Warning, TEXT("ERROR"));

        }



    } else {

        // TODO: Tratar con niveles que no existen, en la build final probablemente no haga falta este check

        UE_LOG(LogTemp, Warning, TEXT("EL NIVEL NO EXISTE"));

        // Por ahora, redirigir al menú principal
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("NivelMenu"));



    }


}





TArray<int> AGameMode_EnPartida::ObtenerCostesDeTorres(TArray<int> IDs) {

    TArray<int> ListaCostes;

    for (int ID : IDs) {
        ListaCostes.Add(ConstructoraDeBlueprints::GetConstructoraDeBlueprints()->GetCosteDeTorre(ID));
    }
    return ListaCostes;
    
}
TArray<float> AGameMode_EnPartida::ObtenerRecargasDeTorres(TArray<int> IDs) {

    TArray<float> ListaRecargas;

    for (int ID : IDs) {
        ListaRecargas.Add(ConstructoraDeBlueprints::GetConstructoraDeBlueprints()->GetTiempoDeRecargaDeTorre(ID));
    }
    return ListaRecargas;


}

TArray<bool> AGameMode_EnPartida::ObtenerEmpiezaRecargadosTorres(TArray<int> IDs) {
        
    TArray<bool> ListaRecargaEmpezada;

    for (int ID : IDs) {
        ListaRecargaEmpezada.Add(ConstructoraDeBlueprints::GetConstructoraDeBlueprints()->GetEmpiezaRecargadaTorre(ID));
    }
    return ListaRecargaEmpezada;
}	


TArray<UTexture2D*> AGameMode_EnPartida::ObtenerImagenesDeTorres(TArray<int> IDs) {
    
    TArray<UTexture2D*> ListaTexturas;

    for (int ID : IDs) { 
        FString Ruta = TEXT("/Game/Assets/Texturas/Torre") + FString::Printf(TEXT("%d"), ID);
        UTexture2D* Textura = LoadObject<UTexture2D>(nullptr, *Ruta);

        ListaTexturas.Add(Textura);
    }
    return ListaTexturas;
}
