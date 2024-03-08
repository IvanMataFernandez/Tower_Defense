// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController_EnPartida.h"
#include "Casilla.h"



void APlayerController_EnPartida::BeginPlay() {
    Super::BeginPlay();
    bShowMouseCursor = true;

}

void APlayerController_EnPartida::Pinchar() {
	FHitResult Resultado;
    APlayerController::GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false , Resultado);
    AActor* Target = Resultado.GetActor();
   
    ACasilla* Casilla = Cast<ACasilla>(Target);


    if (Casilla) {
        Casilla->IntentarColocarTorre(); 
    } else {
        UE_LOG(LogTemp, Display, TEXT("Pincha en una casilla bumfuzzle"));
    }


}