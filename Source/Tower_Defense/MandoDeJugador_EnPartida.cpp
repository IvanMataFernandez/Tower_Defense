// Fill out your copyright notice in the Description page of Project Settings.


#include "MandoDeJugador_EnPartida.h"
#include "Casilla.h"
#include "Torre_Disparador.h"
#include "ConstructoraDeBlueprints.h"
#include "Blueprint/UserWidget.h"



void AMandoDeJugador_EnPartida::BeginPlay() {
    Super::BeginPlay();
    bShowMouseCursor = true;

    this->HUD = CreateWidget(this, this->ClaseHUD);
    this->HUD->AddToViewport();

}





void AMandoDeJugador_EnPartida::Pinchar() {
	FHitResult Resultado;
    APlayerController::GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel8, false , Resultado); 
    AActor* Target = Resultado.GetActor();   
   
    ACasilla* Casilla = Cast<ACasilla>(Target);


    if (Casilla && Casilla->CasillaVacia()) { // Comprobar si la casilla pinchada está vacía
        this->SettearSeleccionDeTorre(); // Recoger el ID desde la UI
        if (SeleccionDeTorre != -1) { // Si había selección en UI
            Casilla->SpawnearTorre(this->SeleccionDeTorre); // Entonces poner la torre elegida en la casilla
        }
    } 


    

}