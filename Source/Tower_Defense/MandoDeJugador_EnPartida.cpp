// Fill out your copyright notice in the Description page of Project Settings.


#include "MandoDeJugador_EnPartida.h"
#include "Casilla.h"
#include "Torre_Disparador.h"
#include "Blueprint/UserWidget.h"
#include "Torre_Producidor.h"
#include "Engine/Texture2D.h"
#include "GameMode_EnPartida.h"
#include "Engine/World.h"
#include "ConstructoraDeBlueprints.h"
#include "Guardador.h"
#include "Kismet/GameplayStatics.h"



// El mando de jugador usado para cuando se está jugando una partida.
// Este trackea que torre está elegiendo el jugador, así como su cantidad de energía y el estado de recarga de sus torres


void AMandoDeJugador_EnPartida::BeginPlay() {

    Super::BeginPlay();
    bShowMouseCursor = true;
    this->EnPartida = false;


    // Obtener de la save que torres desbloqueó el jugador, para saber que torres cargar después

    UGuardador* Guardado = Cast<UGuardador>(UGameplayStatics::LoadGameFromSlot(TEXT("save"), 0));
    this->IDsTorresDesbloqueadas = Guardado->IDsTorresDesbloqueadas;


}


void AMandoDeJugador_EnPartida::Pausar() {
    this->SetPause(true);
}   

void AMandoDeJugador_EnPartida::PausarEn(float Segundos) {
    FTimerHandle TimerParaPausa;
    GetWorld()->GetTimerManager().SetTimer(TimerParaPausa, this, &AMandoDeJugador_EnPartida::Pausar,Segundos, false);               

}

UUserWidget* AMandoDeJugador_EnPartida::CrearHUD(int Seleccion) {

    // Cargar la interfaz elegida según su ID. Mantiene interfaces anteriores activas.

    UUserWidget* HUD;
    if (Seleccion == 0) {
        HUD = CreateWidget(this, this->ClaseHUDElegirTorre);
    } else if (Seleccion == 1) {
        HUD = CreateWidget(this, this->ClaseHUDCuentaAtras);

    } else if (Seleccion == 2) {
        HUD = CreateWidget(this, this->ClaseHUDEnPartida);
    } else if (Seleccion == 3) {
        HUD = CreateWidget(this, this->ClaseHUDDerrota);

    } else if (Seleccion == 4) {
        HUD = CreateWidget(this, this->ClaseHUDVictoria);

    } else {
        HUD = CreateWidget(this, this->ClaseHUDPausa);
        
    }

    HUD->AddToViewport();
    this->HUDs.Add(HUD);

    return HUD;

}



UUserWidget* AMandoDeJugador_EnPartida::ObtenerHUD(int Pos) const {

    if (Pos >= 0 && Pos < this->HUDs.Num()) {
        return this->HUDs[Pos];

    } else {
        return nullptr;
    }


}




void AMandoDeJugador_EnPartida::QuitarUltimaHUDAnadida()  {
    this->QuitarHUD(this->HUDs.Num()-1);
}

void AMandoDeJugador_EnPartida::QuitarHUD(int Pos)  {

    // Pre: Pos en array
    // POst: Quitar la Interfaz en la posición Pos

    this->HUDs[Pos]->RemoveFromParent();
    this->HUDs.RemoveAt(Pos);




}





void AMandoDeJugador_EnPartida::Pinchar() {

    // Procesar un click en la pantalla que no sea en una UI


    if (!this->EnPartida) {return;} // Si todavía se está en la selección de torres, ignorar cualquier tipo de click en el ambiente porque no importan clicks
                                    // que no sean a UIs si no se está jugando activamente en un nivel.

	
    

    // Ver que se pinchó

    FHitResult Resultado;
    APlayerController::GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel8, false , Resultado); 
    AActor* Target = Resultado.GetActor();   
    




    ACasilla* Casilla = Cast<ACasilla>(Target);

    if (Casilla) { // Si se pinchó en una casilla...


        if (Casilla->CasillaVacia()) { // Si la casilla está vacía...

            // La casilla esta vacia, asumimos que el player quiere poner una torre aqui


            ConstructoraDeBlueprints* CdB = ConstructoraDeBlueprints::GetConstructoraDeBlueprints();

            int IDTorreElegida = this->ObtenerIDDeTorreElegidaEnPartida(); // this->SeleccionDelJugador indica que slot está marcado,
                                                                           // obtener el ID de la torre que aloja el slot
            int PosicionTorreEnUI = this->SeleccionDelJugador;
 
            /* Comprobar si la torre es colacable, para ello:
                - Debe haber una torre seleccionada (aparece marcado en verde en UI)
                - La torre a colocar en cuestión debe ser una instant kill (bomba)
                  o no deben haber robots pisando la segunda mitad (trozo izquierdo) de la casilla

                Si este paso falla, no se hace nada más

            */

            if (IDTorreElegida != -1 && (CdB->TorrePermiteOverlappearRobot(IDTorreElegida) || !Casilla->RobotPisandoFinalDeCasilla())) { 

                // Se permite colocar la torre seleccionada

                Casilla->SpawnearTorre(IDTorreElegida); // Entonces poner la torre elegida en la casilla
                
                this->UsarSeleccionElegida(); // Desmarcar la torre elegida en el mando
                this->NotificarAInterfazColoqueTorre(PosicionTorreEnUI); // Y notificar esto mismo a la interfaz para que lo haga visualmente
            }

        

        } else if (this->TNTElegida()) {  // Si la TNT está elegida..

            Casilla->DestruirTorre(); // Si lo está, quitamos la torre de la casilla elegida (si había, si no, no hace nada)

            this->UsarSeleccionElegida(); // Desmarcar la selección de la TNT en el mando
            this->NotificarAInterfazUsoTNT(); // Decirle a la UI que lo haga visualmente también

        } else { // Si no se tiene la TNT elegida  pero la casilla no esta vacía, comprobar si la casilla pinchada aloja un producidor

                ATorre_Producidor* TorreProducidor = Cast<ATorre_Producidor>(Casilla->ObtenerTorreEnCasilla());

                if (TorreProducidor) {
                    // Si lo hace, tratar de recolectar su energia
                    TorreProducidor->Click();
                }
        }

        
    } else {

        // Si no es una casilla, comprobar si es un producidor de energia (requieren ser pinchados para recolectar energia)

        ATorre_Producidor* Torre = Cast<ATorre_Producidor>(Target);

        if (Torre) {

            // Si lo es, ver si tenemos la TNT seleccionada
            
            if (this->TNTElegida()) {

                // TNT seleccionada, vamos a su casilla para borrar la Torre 

                ACasilla* CasillaDeTorre = Cast<ACasilla>(Torre->GetOwner());

                if (CasillaDeTorre) {

                    // Casilla encontrada, hacer los mismos pasos para quitar la torre

                    this->UsarSeleccionElegida();
                    this->NotificarAInterfazUsoTNT();

                    CasillaDeTorre->DestruirTorre();
                }


            } else {

                // TNT no seleccionada, recolectar energia en su lugar

                Torre->Click();
            }
        }





    }

  
    

    

}

void AMandoDeJugador_EnPartida::ObtenerTodasLasImagenesYCostesDeTorre(TArray<UTexture2D*>& Imagenes, TArray<int>& Costes) const {

    // Devuelve en dos listas las imagenes de slots de las torres desbloquadas, así como sus costes
   
    Imagenes.Empty();
    Costes.Empty();

    for (int ID : this->IDsTorresDesbloqueadas) {
        Imagenes.Add(this->ObtenerImagenDeTorre(ID));
    }

    for (int ID : this->IDsTorresDesbloqueadas) {
        Costes.Add(this->ObtenerCosteDeTorre(ID));
    }

}



UTexture2D* AMandoDeJugador_EnPartida::ObtenerImagenDeTorre(int ID) const {
    


    ConstructoraDeBlueprints* CdB = ConstructoraDeBlueprints::GetConstructoraDeBlueprints();
    return CdB->ObtenerImagenDeTorre(ID);
}



int AMandoDeJugador_EnPartida::ObtenerCosteDeTorre(int ID) const {



    ConstructoraDeBlueprints* CdB = ConstructoraDeBlueprints::GetConstructoraDeBlueprints();
    return CdB->GetCosteDeTorre(ID);
}

float AMandoDeJugador_EnPartida::ObtenerRecargaDeTorre(int ID) const {


    ConstructoraDeBlueprints* CdB = ConstructoraDeBlueprints::GetConstructoraDeBlueprints();
    return CdB->GetTiempoDeRecargaDeTorre(ID);


}

bool AMandoDeJugador_EnPartida::ObtenerEmpiezaRecargadoTorre(int ID) const {


    ConstructoraDeBlueprints* CdB = ConstructoraDeBlueprints::GetConstructoraDeBlueprints();
 
    return CdB->GetEmpiezaRecargadaTorre(ID);
}	







int AMandoDeJugador_EnPartida::SlotDeTorreDesbloqueadaEnPosDeSeleccion(int Slot) {

    // Post: Busca si la torre número slot desbloqueada en la save está añadida ya en la seleccion de torres del jugador del nivel
    //       actual. Returns la posicion si true, -1 si no está
    
    int ID = this->IDsTorresDesbloqueadas[Slot];

    for (int Pos = 0; Pos != this->IDsDeTorresElegidas.Num(); Pos++) {
        if (this->IDsDeTorresElegidas[Pos] == ID) {
            return Pos;
        }
    }

    return -1;
}

int AMandoDeJugador_EnPartida::IDDeTorreASlotDeSave(int ID) {

    // Post: Recoge el id de torre pedido y busca la posicion en la que se desbloquea en el juego

    for (int Pos = 0; Pos != this->IDsTorresDesbloqueadas.Num(); Pos++) {
        if (this->IDsTorresDesbloqueadas[Pos] == ID) {
            return Pos;
        }
    }

    return -1;
}

void AMandoDeJugador_EnPartida::ProcesarClickEnSeleccionInicialDeTorres(int Slot, bool& AccionValida, bool& Eliminacion, int& CantidadSelecciones, TArray<int>& SlotsARetroceder, bool& PermiteEmpezar) {



    //   In: El slot pinchado. Cada slot es un tipo de torre distinto (el panel es el 0, el cañón el 1...)
    // Post: AccionValida: Si se hizo algun cambio en el array
    //       Elimnacion: Si la accion realizada fue una eliminacion y no una insercion
    //       CantidadSelecciones: Tras la accion, cuantas torres hay elegidas
    //       SlotsARetrocder: las cards que deberían retroceder un espacio visualmente debido a una eliminación
    //       PermiteEmpezar: Si tras la accion hay 6 torres elegidas or todas las torres desbloqueadas están elegidas

    int PosSeleccion = this->SlotDeTorreDesbloqueadaEnPosDeSeleccion(Slot); // Comprobar si la torre está elegida
    AccionValida = true;

    if (PosSeleccion == -1) {
        Eliminacion = false;
        // No está elegida, comprobar si se puede añadir (hay 6 huecos en el layout, ver si no hay 6 torres elegidas)


        if (this->IDsDeTorresElegidas.Num() != 6) {
            
            // Hay hueco, insertar la torre al final de la lista 


            this->IDsDeTorresElegidas.Add(this->IDsTorresDesbloqueadas[Slot]);

            // Se permite empezar si hay 6 torres elegidas o todas las desbloqueadas están elegidas

            PermiteEmpezar = this->IDsDeTorresElegidas.Num() == 6 || this->IDsDeTorresElegidas.Num() == this->IDsTorresDesbloqueadas.Num();

        } else {

            // No hay hueco, el usuario ya tiene 6 torres elegidas.


            PermiteEmpezar = true;
            AccionValida = false;
        }



    } else {
        // Está elegida, proceder a quitarla de la lista. Se informa a la UI también de la posición de la lista con PosSeleccion a quitar visualmente
        Eliminacion = true;
        PermiteEmpezar = false;  // Tras quitar una torre debe haber al menos un espacio libre, por lo que no se permite empezar


        for (int Pos = PosSeleccion+1; Pos != this->IDsDeTorresElegidas.Num(); Pos++) {
            SlotsARetroceder.Add(this->IDDeTorreASlotDeSave(this->IDsDeTorresElegidas[Pos]));

        }


        this->IDsDeTorresElegidas.RemoveAt(PosSeleccion); // Usar borrado más lento shifteando las posiciones del array hacia adelante para que encaje visualmente con la UI


    }
    CantidadSelecciones = this->IDsDeTorresElegidas.Num();
}





TArray<int> AMandoDeJugador_EnPartida::GetTorresElegidas() const {


    return this->IDsDeTorresElegidas;
}


void AMandoDeJugador_EnPartida::InicializarVariablesDePartida() {


    // Leyendo las torres elegidas para el nivel, carga sus costes y sus tiempos de recarga, así como si deberíane empezar cargadas en el nivel o no
    // Inicializa también la selección de torre actual del jugador a nada y su cantidad de energía a 40

    ConstructoraDeBlueprints* CdB = ConstructoraDeBlueprints::GetConstructoraDeBlueprints();
    UWorld* Mundo = GetWorld();
    
    for (int ID : this->IDsDeTorresElegidas) {
        int TiempoDeRecarga = CdB->GetTiempoDeRecargaDeTorre(ID);

        this->TiempoDeRecargaDeTorres.Add(TiempoDeRecarga);
        this->CosteDeTorres.Add(CdB->GetCosteDeTorre(ID));


        if (ConstructoraDeBlueprints::GetConstructoraDeBlueprints()->GetEmpiezaRecargadaTorre(ID)) {
            this->MomentoEnQueTorreRecarga.Add(Mundo->GetTimeSeconds());

        } else {
            this->MomentoEnQueTorreRecarga.Add(TiempoDeRecarga + Mundo->GetTimeSeconds());

        }


    }

 
	this->SeleccionDelJugador = -1;
	this->Energia = 40;
    this->EnPartida = true; // FLaggear en partida para permitir clicks a casillas 


}


// Métodos que la UI usa para comunicarse con el controller para procesar clicks en las selecciones de torres.


// Procesar click en torre

void AMandoDeJugador_EnPartida::ElegirTorre(int PosTorre, bool& Encender, bool& Correcto, int& SeleccionPrevia) {

    // Pre: Indica la torre que se ha pinchado
    // Post:
    /*
       Encender: Si se debe encender o apagar la seleccion
       Correcto: Si se debe marcar como verde o rojo la seleccion
       SelPrevia: La seleccion previa que se hizo (para apagarla)
    
    */


    // Necesitamos está información para saber que casilla nueva marcar y cual desmarcar en UI

    /*
        Para ello, usa actualiza la variable SeleccionDelJugador que toma como valores según el último click del usuario en la UI:

         -1  no habia seleccion
        0-5  la torre elegida actualmente empezando por la izquierda (se ve en UI marcada en verde)
        6    la TNT elegida actualmente (se ve en UI marcada en verde)
        6-11 la torre elegida incorrectamente empezando por la izquierda (no estaba off cooldown o no teniamos suficiente energia) 
             (se ve en UI marcada en rojo por 1s antes desmarcase ella sola)
             (aunque la UI la desmarca tras un timer, el controller sigue recordando dicho click hasta que se pinche en otra cosa)
    
    
    */

    // Computar la selección anterior (seleccion > 6 indica pinchar en torres no permitibles, seleccion == 6 pinchar en TNT, seleccion < 6 pinchar en torres)

    if (this->SeleccionDelJugador > 6) {
        SeleccionPrevia = this->SeleccionDelJugador - 7;
    } else {
        SeleccionPrevia = this->SeleccionDelJugador;
    }

    

    // Ver si nos podemos permitir la torre y esta off cooldown

    if (this->Energia >= this->CosteDeTorres[PosTorre] && GetWorld()->GetTimeSeconds() >= this->MomentoEnQueTorreRecarga[PosTorre]) {

        // Se puede pinchar, ver si estaba ya elegida de antes

        if (this->SeleccionDelJugador == PosTorre) {
            // Lo estaba, deseleccionar
            this->SeleccionDelJugador = -1;
            
            Encender = false;

        } else {
            // No lo estaba, seleccionar
            this->SeleccionDelJugador = PosTorre;
            
            Encender = true;
        }



        Correcto = true;
    } else {

        // No nos lo podemos permitir, marcar como seleccion erronea

        this->SeleccionDelJugador = PosTorre+7;

        Correcto = false;   
    }

}


// Procesar click en TNT

void AMandoDeJugador_EnPartida::ElegirTNT(int& SeleccionPrevia, bool& TntElegida) {
    

    // Computar seleccion previa, indica solo el último slot pinchado, sin especificar si fue un click correcto o no

    if (this->SeleccionDelJugador > 6) {
        SeleccionPrevia = this->SeleccionDelJugador - 7;
    } else {
        SeleccionPrevia = this->SeleccionDelJugador;
    }


    // Ver si la TNT está elegida ya

    if (this->SeleccionDelJugador != 6) {

        // No lo está, elegirla

        this->SeleccionDelJugador = 6;
        TntElegida = true;

    } else {

        // Lo está, deseleccionar

        this->SeleccionDelJugador = -1;
        TntElegida = false;

    }

}



void AMandoDeJugador_EnPartida::ObtenerUltimaSeleccionTorre(int& Seleccion, bool& Correcto) const {
    
    if (this->SeleccionDelJugador > 6) {
        Seleccion = this->SeleccionDelJugador - 7;
        Correcto = false;
    } else {
        Seleccion = this->SeleccionDelJugador;
        Correcto = true;
    }

}
void AMandoDeJugador_EnPartida::ActualizarEnergiaPor(int Surplus) {

    // Actualizar la cantidad de energia en el controller e informar a la UI de que los actualice visualmente

    this->Energia = this->Energia + Surplus;
    this->NotificarAInterfazCambioEnDinero(this->Energia);

}


// Los mátodos que procesan un click en una casilla 

void AMandoDeJugador_EnPartida::UsarSeleccionElegida() {

    // Procesa el click en una casilla, quitando la seleccion y restando el coste de la torre elegida si había. Además, vuelve a refrescar el cooldown de dicha torre elegida

    // Ver si una torre fue elegida correctamente
    if (this->SeleccionDelJugador != -1 && this->SeleccionDelJugador < 6) {

        // Lo está, restar su coste a la energía actual del jugador, calcular cuando estará disponible tras recarga para permitir colocar de nuevo

        this->ActualizarEnergiaPor(-this->CosteDeTorres[this->SeleccionDelJugador]); // restar
        this->MomentoEnQueTorreRecarga[SeleccionDelJugador] = GetWorld()->GetTimeSeconds() + this->TiempoDeRecargaDeTorres[this->SeleccionDelJugador]; // calcular recarga
    }

    this->SeleccionDelJugador = -1; // Deseleccionar la seleccion de torre en todo caso tras pinchar en una casilla

}


int AMandoDeJugador_EnPartida::ObtenerCantidadEnergia() const {
    return this->Energia;
}

bool AMandoDeJugador_EnPartida::TNTElegida() {
    return  this->SeleccionDelJugador == 6;

}

int AMandoDeJugador_EnPartida::ObtenerIDDeTorreElegidaEnPartida() {

    // Devuelve la torre elegida actualmente si hay. -1 si no hay torre elegida.


    
    if (this->SeleccionDelJugador >= 0 && this->SeleccionDelJugador < 6) {
        return this->IDsDeTorresElegidas[this->SeleccionDelJugador];

    } else {
        return -1;

    }
}
