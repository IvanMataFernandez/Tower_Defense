// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn_EnPartida.h"
#include "Casilla.h"
#include "MandoDeJugador_EnPartida.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerPawn_EnPartida::APlayerPawn_EnPartida()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerPawn_EnPartida::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn_EnPartida::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn_EnPartida::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("Pinchar"), IE_Pressed, this, &APlayerPawn_EnPartida::Pinchar);

}


void APlayerPawn_EnPartida::Pinchar() {
	Cast<AMandoDeJugador_EnPartida>(UGameplayStatics::GetPlayerController(this, 0))->Pinchar();

}


