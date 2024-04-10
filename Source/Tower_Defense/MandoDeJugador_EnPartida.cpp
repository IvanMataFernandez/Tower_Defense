// Fill out your copyright notice in the Description page of Project Settings.


#include "MandoDeJugador_EnPartida.h"
#include "Casilla.h"
#include "Torre_Disparador.h"
#include "Blueprint/UserWidget.h"
#include "Torre_Producidor.h"
#include "Engine/Texture2D.h"



void AMandoDeJugador_EnPartida::BeginPlay() {

    Super::BeginPlay();
    bShowMouseCursor = true;



}

UUserWidget* AMandoDeJugador_EnPartida::CrearHUD(int Seleccion) {


    if (Seleccion == 0) {
        this->HUD = CreateWidget(this, this->ClaseHUDElegirTorre);
    } else if (Seleccion == 1) {
        this->HUD = CreateWidget(this, this->ClaseHUDEnPartida);

    } else {
        this->HUD = CreateWidget(this, this->ClaseHUDDerrota);
    }
    this->HUD->AddToViewport();
    return this->HUD;

}



UUserWidget* AMandoDeJugador_EnPartida::ObtenerHUD() const {
    return this->HUD;
}



void AMandoDeJugador_EnPartida::SetTorresElegidas(TArray<int> IDs) {
    this->IDTorresElegidas = IDs;
}

TArray<int> AMandoDeJugador_EnPartida::GetTorresElegidas() const {
    return this->IDTorresElegidas;
}



void AMandoDeJugador_EnPartida::Pinchar() {
	FHitResult Resultado;
    APlayerController::GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel8, false , Resultado); 
    AActor* Target = Resultado.GetActor();   
   


    // Comprobar si se quiere usar la pala

    ACasilla* Casilla = Cast<ACasilla>(Target);

    if (Casilla) {


        if (Casilla->CasillaVacia()) {

            // La casilla esta vacia, asumimos que el player quiere poner una torre aqui

            this->SettearSeleccionDeTorre(); // Recoger el ID desde la UI
            
            if (this->SeleccionDeTorre != -1) { // Si había selección en UI de Torre Correcta.
                Casilla->SpawnearTorre(this->SeleccionDeTorre); // Entonces poner la torre elegida en la casilla
            }

        } else {

            // Comprobar si el quitador (equivalente Pala en PvZ) está seleccionado
            this->SettearBorradorDeTorre();

            if (this->SeleccionDeTorre == 1) { 

                Casilla->QuitarTorre(); // Si lo está, quitamos la torre del nivel

            } 
        }

    } else {

        // Si no es una casilla, comprobar si es un producidor de energia (requieren ser pinchados para recolectar energia)

        ATorre_Producidor* Torre = Cast<ATorre_Producidor>(Target);

        if (Torre) {

            // Si lo es, ver si tenemos la "pala" seleccionada
            this->SettearBorradorDeTorre();
            
            if (this->SeleccionDeTorre == 1) {

                // Pala seleccionada, vamos a su casilla para borrar la Torre (si no tiene casilla relacionada como el panel por defecto, entonces no hace nada)

                ACasilla* CasillaDeTorre = Cast<ACasilla>(Torre->GetOwner());

                if (CasillaDeTorre) {
                    CasillaDeTorre->QuitarTorre();
                }


            } else {

                // Pala no seleccionada, recolectar energia en su lugar

                Torre->Click();
            }
        }





    }

  
    

    

}

