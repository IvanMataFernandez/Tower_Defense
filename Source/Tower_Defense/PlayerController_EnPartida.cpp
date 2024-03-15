// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController_EnPartida.h"
#include "Casilla.h"
#include "Torre_Disparador.h"



void APlayerController_EnPartida::BeginPlay() {
    Super::BeginPlay();
    bShowMouseCursor = true;

}

void APlayerController_EnPartida::Pinchar() {
	FHitResult Resultado;
    APlayerController::GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false , Resultado); // TODO: Considerar crear un Trace Channel exclusivo para las casillas. 
    AActor* Target = Resultado.GetActor();                                                              // De forma que se pueda pinchar en ellas mas facil para colocar torres
   
    ACasilla* Casilla = Cast<ACasilla>(Target);


    if (Casilla) {
        Casilla->IntentarColocarTorre(); 
    } else {
        UE_LOG(LogTemp, Display, TEXT("Pincha en una casilla bumfuzzle"));
    }


    /*

    ATorre_Disparador* Torre = Cast<ATorre_Disparador>(Target);

    if (Torre) {
        Torre->ClearTimer();
    }
    */
    

}