// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode_EnPartida.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonReader.h"
#include "ZonaSpawnRobot.h"
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







// El gamemode que se encarga de arbitrar la pantalla de selección de torres y el main loop del juego. Usa archivos .json para cargar
// las oleadas de enemigos del nivel. Todos los niveles usan el mismo gamemode, solo que cargan un json distinto que dicta que enemigos
// deberían aparecer



// Called when the game starts or when spawned
void AGameMode_EnPartida::BeginPlay()
{
	Super::BeginPlay();




   
    this->ZonaSpawn = Cast<AZonaSpawnRobot>(UGameplayStatics::GetActorOfClass(GetWorld(), AZonaSpawnRobot::StaticClass()));
    this->ZonaSpawnPreview = Cast<AZonaSpawnRobotPreview>(UGameplayStatics::GetActorOfClass(GetWorld(), AZonaSpawnRobotPreview::StaticClass()));
    this->Camara = Cast<APlayerPawn_EnPartida>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());

    if (this->ZonaSpawn && this->ZonaSpawnPreview ) {

      //  this->TocarMusica(3);  --> Por defecto AmbientSound del nivel empieza tocando la musica 3, la de pantalla de selección. Esta instrucción es omitible


        // Cargar el número del nivel actual 

        UGuardador* Guardado = Cast<UGuardador>(UGameplayStatics::LoadGameFromSlot(TEXT("save"), 0));
        this->NivelActual = Guardado->Nivel;


        // Cargar info del nivel actual basado en el nivel en el que estamos

        if (this->CargarNivel(this->NivelActual)) {

            // Carga correcta del nivel
            // Esperar 0.5s para empezar a mover la camara

            FTimerHandle Espera;
            GetWorld()->GetTimerManager().SetTimer(Espera, this->Camara, &APlayerPawn_EnPartida::MoverCamASeleccion, 0.5f, false);   


            // Cuando la camara acabe de moverse, se ejecuta:  this->EmpezarSeleccionDeTorres();


        } else {
            
            // Si hay fallo de carga de nivel (falta el json, no usa formato adecuado...), procesar el método de fallback de error de juego
            this->ProcesarCorrupcionDeDatos();
        }
    
    






    } else {
        UE_LOG(LogTemp, Error, TEXT("No hay zonas de spawn / reproductor"));
    }



           

}

void AGameMode_EnPartida::EmpezarSeleccionDeTorres() {


    // La camara se ha movido ya hacia la derecha. Empezar a ejecutar la lógica de la selección de torres.


    // Spawnear los bots de preview para ver contra quien nos enfrentamos en el nivel
    this->SpawnearRobotsPreview();


    // Esperar un par de segundos para que los bots se acerquen antes de dar la opcion al usuario de que elija sus torres. Cuando acabe la espera
    // se abre la interfaz que permite seleccionar las torres (implementado en blueprints)
    
    FTimerHandle Espera;
    GetWorld()->GetTimerManager().SetTimer(Espera, this, &AGameMode_EnPartida::CrearInterfazSeleccionDeTorres, 4.5f, false);               


}


void AGameMode_EnPartida::SpawnearRobotsPreview() {

    int PesoMax = 0;
    float RobotsTotalesPorTipoF = (FMath::RandRange(8,12) + 4 * (this->IDsRobot.Num()-1)) / this->IDsRobot.Num() ; // Spawnear en preview. Contra más tipos de bots, dar mas peso porque se pierde en redondeos
    int RobotsTotalesPorTipo = FMath::RoundToInt(RobotsTotalesPorTipoF);
    TArray<int> RobotsASpawnear;

    // Por cada tipo de robot, ver cuantos caben en la preview segun el peso maximo seleccionado. Almacenarlos en el Array de robots a spawnear

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

    // Finalmente, spawnear dichos robots para que empiecen a moverse hacia nosotros y los podamos ver

    for (int ID: RobotsASpawnearShuffled) {
        this->ZonaSpawnPreview->SpawnearRobot(ID);
    }



}

void AGameMode_EnPartida::FinSeleccionTorres() {


    // Se ha pinchado en el botón de confirmar selección de torres en la UI:

    this->Camara->MoverCamAJugar(); // Mover la camara de nuevo a la izquierda para poder jugar


  
    // Tras acabar de mover la cam, se llama a CargarCuentaAtrasParaEmpezarJuego()

}

void AGameMode_EnPartida::CargarCuentaAtrasParaEmpezarJuego() {

    this->EliminarRobotsPreview(); // Quitar los robots de la pantalla de preview para que no consuman recursos (no son visibles desde nuestra cam)

    this->CrearInterfazDeCuentaAtras(); // Cargar la cuenta atrás para empezar el nivel (desde blueprints porque es otra UI)
    // Hacer sonar cuenta atrás            
    this->TocarMusica(4);

    // Al acabar la cuenta atrás se llama a EmpezarJuego()

}



void AGameMode_EnPartida::EliminarRobotsPreview() {

    // Quitar los bots de la preview cuando se empieza a jugar porque ya no se ven de todas formas y consumen recursos

    TArray<AActor*> RobotsPreview;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARobot::StaticClass(), RobotsPreview);

    for (AActor* Robot: RobotsPreview) {
        Robot->Destroy();
    }
   
}


void AGameMode_EnPartida::EmpezarJuego() {


    // Con esto se empieza a jugar el nivel

    // Cargar variables básicas para trackear el estado del juego

    this->PesoRobotsVivo = 0; // Al principio no hay robots vivos (no han spawneado todavía)
    this->OleadaActual = -1; // Las oleadas van como un iterador, 0 based indexing. -1 quiere decir que no está apuntando a ninguna oleada
    this->SeQuiereSpawnearLaSiguienteOleada = false; // No spawnear la siguiente oleada si no se ha alcanzado el threshold de robots a matar de la oleada actual
    this->VictoriaPosible = false; // No es la última oleada todavía


    this->TocarMusica(0); // Tocar la música de la partida en sí


    // Inicializar el mando de juego, para que cargue los costes y tiempos de recarga de las torres elegidas, así como inicialice nuestra energía inicial para comprar torres
    Cast<AMandoDeJugador_EnPartida>(GetWorld()->GetFirstPlayerController())->InicializarVariablesDePartida(); 
    this->CrearInterfazDePartida(); // Crear la interfaz que nos permite seleccionar torres para colocarlas en el nivel (por blueprints)


    this->EmpezarCargaDePrimeraOleada(); // Bufferear la carga de la primera oleada del nivel

              


}


void AGameMode_EnPartida::EmpezarCargaDePrimeraOleada() {

    // Bufferear la carga de la primera oleada y el efecto de sonido de cuando aparece el primer enemigo del nivel. LA info del tiempo de espera
    // se cargó del json al cargar la información del nivel

    GetWorld()->GetTimerManager().SetTimer(this->TimerParaOleadas, this, &AGameMode_EnPartida::CargarDatosOleada, this->HastaSiguienteOleada, false);      
    FTimerHandle TimerSFX;         
    GetWorld()->GetTimerManager().SetTimer(TimerSFX, this, &AGameMode_EnPartida::SonarSFXGlobal, this->HastaSiguienteOleada, false);  

}

void AGameMode_EnPartida::CargarDatosOleada() {


    // Se ha esperado ya lo necesario, proceder a materealizar la oleada


    this->OleadaActual++; // Nueva oleada


    // Recopilar datos de oleada actual del array creado a partir del json

    TSharedPtr<FJsonObject> DatosOleadaActual = this->OleadasJson[this->OleadaActual]->AsObject();


    this->PesoRestante = DatosOleadaActual->GetIntegerField(TEXT("Peso")); // Obtener peso permitido para spawnear bots
    this->HastaSiguienteOleada = DatosOleadaActual->GetNumberField(TEXT("tiempoSiguienteOleada")); // OBtener el timer de espera para cargar la siguiente oleada

    



    this->PesoPorEliminarHastaSiguienteOleada = 1 + this->PesoRestante / 2;   // Spawnear la siguiente oleada si muere la mitad del peso de esta + 1

                                                                                    

    // Refrescar listas auxiliares para spawnear bots

    this->PesosRobotActual = this->PesosRobot;
    this->IDsRobotActual = this->IDsRobot;
    this->ProbabilidadesRobotAcumuladas.Empty();

    // Calcular las probabilidades acumuladas para crear probabilidades ponderadas de spawn segun tipo de robot

    TArray<TSharedPtr<FJsonValue>> ListaProbabilidades =  DatosOleadaActual->GetArrayField(TEXT("probabilidades"));
    float ProbabilidadAcumulada = 0.f;



    for (TSharedPtr< FJsonValue>& Probabilidad : ListaProbabilidades) {
            ProbabilidadAcumulada = ProbabilidadAcumulada + Probabilidad->AsNumber(); 
            this->ProbabilidadesRobotAcumuladas.Add(ProbabilidadAcumulada);

    }



    // Bufferear Recopilar datos de siguiente oleada, ver si la siguiente oleada es una oleada grande

    if (this->OleadaActual != this->OleadasTotales-1) {
        this->SeAproximaOrdaGrande = this->GrandesOleadas.Contains(this->OleadaActual+1);
    } else {
        this->SeAproximaOrdaGrande = false;
    }


    // Comprobar que los datos procesados de la oleada actual del nivel han sido correctos y tienen sentido:

    /*
        - Debe haber un campo con la cantidad de peso a spawnear. Debe ser positivo
        - Debe haber un campo en el que indica el tiempo a esperar hasta la siguiente oleada. Debe ser positivo o al menos 10s si se aproxima una gran oleada
          (para asegurarse de que el juego contabilice correctamente la oleada en la que estamos)
        - La lista de probabilidades de spawnear cada robot debe encajar en longitud con la de la cabecera del nivel en la que se indican que robots van a spawnear
        - La suma de las probabilidades a spawnear de los robots debe sumar 1 (con un margen pequeño de error)
    
    
    */

   bool OleadaInvalida = this->PesoRestante <= 0  || (this->HastaSiguienteOleada <= 0.f || 
                         this->SeAproximaOrdaGrande && this->HastaSiguienteOleada < 10.f) || ListaProbabilidades.Num() != this->IDsRobot.Num() || 
                         (ProbabilidadAcumulada < 0.999f || ProbabilidadAcumulada > 1.001f);

    if (OleadaInvalida) {
        // Si la oleada es invalida, se procesa el metodo de corrupcion de datos y se redirige al menú principal
        this->ProcesarCorrupcionDeDatos();
    }

    // Ya que los datos cargados son validos...  Ya se han cargado los datos de esta oleada, programar la siguiente

    this->EmpezarCargaDeSiguienteOleada(); 









    // Ya tenemos los datos de la oleada y son validos, empezar a handlear logica de spawnear enemigos con dicha información


    if (this->GrandesOleadas.Contains(this->OleadaActual)) {
 
        
        // Se aproxima FLAG de robots (oleada grande), esperar unos 6 segundos para mostrar por UI y hacer avisos sonoros antes de empezar a spawnear nada


        GetWorld()->GetTimerManager().SetTimer(this->TimerParaSpawnRobot, this, &AGameMode_EnPartida::GenerarOleadaGrande, 6.f, false);   


        // Cambiar la música también para informar de la orda, la última orda tiene música distinta a las demás
        if (this->OleadaActual != this->OleadasTotales-1) {
            // No ultima orda
             this->TocarMusica(1);     

            this->ComunicarAvisoDeOleadaGrande(false); // Avisar a UI

        }  else {
            // Ultima orda
            this->TocarMusica(2);

            this->ComunicarAvisoDeOleadaGrande(true);

        }          



    } else {

        // Si no es una orda, spawnear la oleada normal ya (no se requieren avisos previos)

        this->GenerarOleada();

    }


}


void AGameMode_EnPartida::EmpezarCargaDeSiguienteOleada() {

    // Si no estamos en la última oleada, programar la carga de la siguiente

    if (this->OleadaActual != this->OleadasTotales-1) { 
        GetWorld()->GetTimerManager().SetTimer(this->TimerParaOleadas, this, &AGameMode_EnPartida::CargarDatosOleada, this->HastaSiguienteOleada, false);               
    }
}



void AGameMode_EnPartida::GenerarOleada() {

    // Se quiere spawnear una oleada normal


    this->ComunicarAvanceOleadaUI(); // Triggear avance en progress bar (por blueprints)
    
    // Reiniciar la zona de spawn para que los bots vuelvan a spawnear delante

    this->ZonaSpawn->RefrescarNuevaOleada();

    this->GenerarRobot(); // Empezar los spawns de robots
}


void AGameMode_EnPartida::GenerarOleadaGrande() {


    // Se quiere spawnear una oleada grande




    this->ComunicarAvanceOleadaUI(); // Triggear avance en progress bar


    // Reiniciar la zona de spawn para que los bots vuelvan a spawnear delante

    this->ZonaSpawn->RefrescarNuevaOleada();


    // Spawnear lider de oleada (tiene coste de peso 1)
    this->SpawnearRobot(-1); 

     // Hacer el spawn del resto de la oleada
     this->GenerarRobot();


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

        // Encontrar donde cae el random para ver que tipo de robot spawnear

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

        
            // Los siguientes pasos mapean la array de probabilidades para adaptar las probabilidades proporcionalmente sin incluir el robot
            // que no nos podemos permitir

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
                
                    ProbabilidadBasePrevia = this->ProbabilidadesRobotAcumuladas[i];
                            


                }




            
            } else {
                // NO SE PUEDE ELEGIR, el resto de bots tienen chance 0% de spawnear en esta wave
                Sel = true;
                Val = false;        
            }





        } else {
            // NO SE PUEDE ELEGIR, todos los robots disponibles en el nivel cuestan más que el budget de oleada actual
            Sel = true;
            Val = false;
        }




    }

    if (Val) { 
        // SPAWN si se puedo elegir bot


        this->SpawnearRobot(Pos);


        if (this->PesoRestante != 0) {
            // Si queda budget, llamar a esta funcion de nuevo para hacer aparecer el siguiente robot
            this->GenerarRobot();

        } else if (this->SeQuiereSpawnearLaSiguienteOleada) {
            
            // Si no queda budget pero se habia triggeado el flag de querer spawnear la siguiente oleada YA, como justo hemos acabdo de spawnear esta, crear la siguiente.

            this->SeQuiereSpawnearLaSiguienteOleada = false;

            // Cancelar la programacion de la siguiente oleada para hacerlo YA en su lugar

            GetWorld()->GetTimerManager().ClearTimer(this->TimerParaOleadas);
            this->CargarDatosOleada();

        }
    
    } else {
        // Si no se pudo spawnear bot porque no tenemos suficente budget, settear el budget a cero para indicar que no hay más spawns
        this->PesoRestante = 0;
    }
 





}


void AGameMode_EnPartida::SpawnearRobot(int Pos) {
    

    // Pos indica la posicion del id de robot en el array de robots disponibles del nivel.
    // Por ejemplo, si se permite basico (id = 0) y bomba (id = 8), el array de disponibilidad es [0,8]
    // Si se desea spawnear basico, se usa pos 0, y para bomba pos 1, ya que esos indexan el array de disponibilidad

    int ID;
    int PesoRobot;
    
    
    if (Pos >= 0) {

        // Obtener del array de disponibilidad el identificador del bot a spawnear y su peso

        ID = this->IDsRobotActual[Pos];
        PesoRobot = this->PesosRobotActual[Pos];

    } else {

        // El bot lider de oleada no se pone en el array de disponibilidad, se da por sentado que siempre esta disponible pero solo uno por cada oleada grande
        // Por ello, ocupa la pos "-1" del array de disponibilidad

        ID = 1;
        PesoRobot = ConstructoraDeBlueprints::GetConstructoraDeBlueprints()->GetPesoDeRobot(ID);

    }

    this->PesoRobotsVivo = this->PesoRobotsVivo + PesoRobot; // Contabilizar el peso de robot en el counter de robots vivos
    this->PesoRestante = this->PesoRestante - PesoRobot; // Restar al budget de oleada




  

    // Spawnear el bot con el ID indicado. La zona de spawn decide en que fila hacerlo aparecer y le settea al Robot spawneado el valor de la oleada actual

    this->ZonaSpawn->SpawnearRobot(ID, this->OleadaActual); 


}




void AGameMode_EnPartida::ProcesarMuerteDeRobot(int PesoDeRobot, ARobot* RobotMatado) {


    // Este método se llama cada vez que muere un robot.

    // Restar el peso del robot de los robots vivos restantes
    this->PesoRobotsVivo = PesoRobotsVivo - PesoDeRobot;

    // Restar el peso del robot del threshold para el spawn de la siguiente oleada si fue spawneado en esta misma oleada

    if (RobotMatado->GetOleada() == this->OleadaActual) {
        this->PesoPorEliminarHastaSiguienteOleada = this->PesoPorEliminarHastaSiguienteOleada -  PesoDeRobot;
    }

    // Determinar wincon / avanzar más rápido en el nivel:

    if (this->OleadaActual != this->OleadasTotales-1) { // Determinar si es la ultima oleada o no

        // Si no lo es, determinar si hemos hitteado el threshold para spawnear la siguiente oleada antes (no se pueden adelantar las oleadas gordas)

        if (!this->SeAproximaOrdaGrande && this->PesoPorEliminarHastaSiguienteOleada <= 0) {

            // Se quiere Adelantar la oleada, para ello mirar si la oleada anterior todavía está spawneando (no debería ser el caso, pero por medida de seguridad)

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



    // Comunicar a la UI de lo ocurrido y de lo que debería mostrar

    int Desbloqueo = this->ConseguirDesbloqueo(this->NivelActual); // Ver que torre desbloqueamos

    if (Desbloqueo != -3) {
        // Si no hay fallo en parseo de datos, comunicar al juego de lo que debería mostrar por pantalla (la torre desbloqueada o algun indicador de nivel superado)
        this->ComunicarVictoria(Desbloqueo, PosicionEnPantalla.X, PosicionEnPantalla.Y); // Implementado en blueprints porque requiere uso de UI

    } else {

        // Si hay fallo, procesar la corrupción de datos

        this->ProcesarCorrupcionDeDatos();


    }   


   
    // Pausar todas las torres porque no se necesitan ya, también se han bloqueado los botones de la interfaz de donde se pueden poner mas torres
    // para no poder colocar mas tras ganar (en blueprint)

    TArray<AActor*> Torres;
    
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATorre::StaticClass(), Torres);

    for (AActor* Torre : Torres) {

        Cast<AEntidad>(Torre)->PausarEntidad();
    }



}

int AGameMode_EnPartida::ConseguirDesbloqueo(int Nivel) {
    
    // Leyendo el nivel que se acaba de superar (valor entre 1 y la cantidad de niveles existentes), se devuelve el id de la torre desbloqueada (valor >= 0)
    // Se puede devolver -1 si no se desbloquea torre, -2 si se completó el último nivel y -3 si hay fallo en el parseo del json

    UGuardador* Guardado = Cast<UGuardador>(UGameplayStatics::LoadGameFromSlot(TEXT("save"), 0));

    // Leer JSON de desbloqueos para ver si desbloqueamos torre nueva

    FString FilePath = FPaths::ProjectContentDir() + FString(TEXT("/InfoDeJuego/Desbloqueos/desbloqueos.json"));
    FString Contenido;

    if (FFileHelper::LoadFileToString(Contenido, *FilePath)) {
      TSharedPtr<FJsonObject> JsonDesbloqueos;

        if (FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Contenido), JsonDesbloqueos)) {

            // Obtener la respuesta correspondiente del array json
            int Desbloqueo = 0;
            TArray<TSharedPtr<FJsonValue>> ArrayDesbloqueos = JsonDesbloqueos->GetArrayField(TEXT("desbloqueos"));

            // Obtener el valor de la torre desbloqueada y ver si es valido.
            /* Un desbloqueo es válido si:
                - Existe un array de desbloqueos en el juego
                - La posicion del nivel apunta a una posicion de dicho array, y es un número (si es string se parsea como 0 en este paso)
                - Dicho número no corresponde al id de una torre que ya tiene el jugador (a no ser que ya haya completado el juego al menos una vez)
                - Si el número no es negativo se asume que es el de una torre, dicha torre debe existir en el código del juego (tiene coste 900+ si no existe)
                - Si el número del desbloqueo es negativo, no debe ser inferior a -2 (-1 indica no desbloqueo y -2 indica que se completó el último nivel).

            */
            bool IDInvalido = ArrayDesbloqueos.Num() < Nivel || !ArrayDesbloqueos[Nivel-1]->TryGetNumber(Desbloqueo) || 
                              (!Guardado->JuegoCompleto && Guardado->IDsTorresDesbloqueadas.Contains(Desbloqueo)) || 
                              (Desbloqueo >= 0 && ConstructoraDeBlueprints::GetConstructoraDeBlueprints()->GetCosteDeTorre(Desbloqueo) >= 900) || 
                               Desbloqueo < -2;
             
            // Si el ID no es válido, se devuelve código de error
            if (IDInvalido) {
                return -3;
            }

            // El ID es válido, procesarlo

            // Comprobar si se desbloquearía una torre nueva y se está en NG+ (ya se pasó el juego entero una vez)
            if (Desbloqueo >= 0 && Guardado->JuegoCompleto) {
                // Es el caso, en su lugar devolver -1 para no desbloquear la torre de nuevo
                return -1;
            } else {
                // No es el caso, dar el valor original (0+ para torre, -1 si el nivel no daba ya desbloqueo o -2 si era el último)
                return Desbloqueo;
            }
           
                    


        } else {
            UE_LOG(LogTemp, Error, TEXT("JSON de desbloqueos no se pudo parsear"));
            return -3;       
        }


    } else {
        UE_LOG(LogTemp, Error, TEXT("JSON de desbloqueos no encontrado"));
        return -3;
    }



}



void AGameMode_EnPartida::ProcesarCorrupcionDeDatos() {

    // Hay datos corrompidos, poner el nivel actual a "-1" para indicar corrupción de datos y volver al menú principal
    UGuardador* Guardado = Cast<UGuardador>(UGameplayStatics::LoadGameFromSlot(TEXT("save"), 0));
    Guardado->Nivel = -1;
    
    // Guardar la save con el nivel en -2
    UGameplayStatics::SaveGameToSlot(Guardado, TEXT("save"), 0);

    // Cargar este nivel de nuevo para que se carge la información del nuevo nivel al que apunta la save ahora (nivel -1 = error en juego)
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("NivelMenu"));
}






void AGameMode_EnPartida::ProcesarClickEnRecompensa() {

    // Cuando se hace click en la recompensa desde el droppeable en UI, se cambia a musica de victoria y se quita la interfaz de EnPartida (esto ultimo en blueprint)

    this->TocarMusica(7);

}


void AGameMode_EnPartida::AvanzarNivel(int TorreDesbloqueo) {

    // Cuando se pincha en siguiente nivel en la UI de victoria, venimos aquí:

    // Pre: Torre desbloqueo contiene la torre a desbloquear para añadir a la save por completar el nivel. 
    // -1 indica que no hubo desbloqueo
    // -2 indica que no hubo desbloqueo y que se completó el último nivel del juego
    
    
    UGuardador* Guardado = Cast<UGuardador>(UGameplayStatics::LoadGameFromSlot(TEXT("save"), 0));
    
    // Avanzar contador del nivel

    Guardado->Nivel = this->NivelActual + 1;

    if (TorreDesbloqueo != -2) {

        // Obtener la save

        if (TorreDesbloqueo >= 0) {
            // Si hubo unlock, añadirlo a la save
            Guardado->IDsTorresDesbloqueadas.Add(TorreDesbloqueo); 
        }

        // Guardar los cambios
        UGameplayStatics::SaveGameToSlot(Guardado, TEXT("save"), 0);

        // Cargar este nivel de nuevo para que se carge la información del nuevo nivel al que apunta la save ahora
        UGameplayStatics::OpenLevel(GetWorld(), TEXT("NivelPrincipal"));
    } else {
        
        // Se completó el último nivel del juego, settear "Nivel" a 0 para indicar esto
        Guardado->Nivel = 0;
        // Guardar los cambios
        UGameplayStatics::SaveGameToSlot(Guardado, TEXT("save"), 0);

        // Redirigir al menú principal (verá que no existe un nivel que cargar y tratará el caso (mostrando un pop-up de felicitaciones por completar el juego))
        UGameplayStatics::OpenLevel(GetWorld(), TEXT("NivelMenu"));


    }




}










TArray<int> AGameMode_EnPartida::EncontrarGrandesOleadas() {

    // Encontrar en el array de oleadas que posiciones incluyen un "flag" (oleada grande)

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

    // Este método se llama cuando un robot hace overlap con la parte izquierda del nivel, tras colarse entre las defensas del jugador


    this->CausanteDerrota = Causante;
    this->TocarMusica(5);
   
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
    
    // Tras mover la cam a la izquierda:

    // Descongelar al robot causante de la derrota, manteniendo el resto del tablero congelado

    this->CausanteDerrota->SetVelocidad(600.f);
    this->CausanteDerrota->DespausarEntidad();

    FTimerHandle TimerParaUI;

    GetWorld()->GetTimerManager().SetTimer(TimerParaUI, this, &AGameMode_EnPartida::FinalizarAnimacionDerrota, 2.f, false); 


}

void AGameMode_EnPartida::FinalizarAnimacionDerrota() {

    // Finalmente cuando el robot ya haya entrado visualmente en la mina del jugador, despawnearlo
    this->CausanteDerrota->Destroy();
    
    this->CrearInterfazDeDerrota(); // Llamado por blueprint
    this->TocarMusica(6); // Hacer sonar música de derrota



}



bool AGameMode_EnPartida::CargarNivel(int Nivel) {

    // Post: Si el nivel se ha cargado correctamente o no, en caso correcto, carga en los atributos de la clase los datos relevantes del nivel, como la info
    //       de oleadas y el tiempo a esperar para hacer aparecer el primer bot en el nivel

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



            TArray<TSharedPtr<FJsonValue>> ListaIDsRobots = JsonNivel->GetArrayField(TEXT("robotsPermitidos"));

            this->HastaSiguienteOleada = JsonNivel->GetNumberField(TEXT("tiempoSinEnemigos")); 




            for (TSharedPtr< FJsonValue>& ValorId : ListaIDsRobots) {
                this->IDsRobot.Add(ValorId->AsNumber());
            }

            // Se han obtenido los robots spawneables, obtener sus pesos ahora

            for (int Id : this->IDsRobot) {
                PesosRobot.Add(ConstructoraDeBlueprints::GetConstructoraDeBlueprints()->GetPesoDeRobot(Id));  
            }

            this->OleadasTotales = this->OleadasJson.Num();
            this->GrandesOleadas = this->EncontrarGrandesOleadas();


            // Comprobar que la descripcion general del nivel es válida y no tiene datos corrompidos:
            /*
    
                - Debe haber un campo que indica el tiempo inicial sin robots
                - Debe haber una lista en la que se dice que robots van a aparecer en el nivel
                - La última oleada del nivel debe ser una gran oleada, además, debe haber al menos una oleada en todo el nivel
                - No pueden haber más de 4 grandes oleadas.
            */


           bool NivelInvalido = this->HastaSiguienteOleada <= 0.f || ListaIDsRobots.Num() == 0 || this->GrandesOleadas.Num() < 1 || 
                                this->GrandesOleadas[this->GrandesOleadas.Num()-1] != this->OleadasTotales-1 || this->GrandesOleadas.Num() > 4;

           return !NivelInvalido;

      

 

        } else {
            // El json no pudo ser parseado

            return false;
        }



    } else {
        // El json del nivel no pudo ser encontrado

        return false;




    }


}










