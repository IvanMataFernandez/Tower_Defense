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
    APlayerController::GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false , Resultado); // TODO: Considerar crear un Trace Channel exclusivo para las casillas. 
    AActor* Target = Resultado.GetActor();                                                              // De forma que se pueda pinchar en ellas mas facil para colocar torres
   
    ACasilla* Casilla = Cast<ACasilla>(Target);


    if (Casilla && Casilla->CasillaVacia()) {
        this->SettearSeleccionDeTorre();
        if (SeleccionDeTorre != -1) {
        Casilla->ColocarTorre(this->SeleccionDeTorre); 

        }
    } else {
        UE_LOG(LogTemp, Display, TEXT("Pincha en una casilla bumfuzzle"));
    }


    

}