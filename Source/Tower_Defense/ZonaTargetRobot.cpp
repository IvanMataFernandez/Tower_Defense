// Fill out your copyright notice in the Description page of Project Settings.


#include "ZonaTargetRobot.h"
#include "Components/BoxComponent.h"
#include "Robot.h"
#include "GameMode_EnPartida.h"
#include "Kismet/GameplayStatics.h"


// La zona que triggerea el game over si un robot la toca. Está a la izquierda del nivel


AZonaTargetRobot::AZonaTargetRobot()
{
	PrimaryActorTick.bCanEverTick = false;


	this->ZonaTarget = CreateDefaultSubobject<UBoxComponent>(TEXT("Zona Target"));
	RootComponent = this->ZonaTarget;
	this->ZonaTarget->OnComponentBeginOverlap.AddDynamic(this, &AZonaTargetRobot::EnOverlap);
}

// Called when the game starts or when spawned
void AZonaTargetRobot::BeginPlay()
{
	Super::BeginPlay();

             

}

void AZonaTargetRobot::EnOverlap(UPrimitiveComponent* OverlapComp, AActor* OtroActor, UPrimitiveComponent* OtroComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	// El evento que se triggea cuando algo choca contra la zona

	// Puede ser posible que un proyectil triggeé este evento para eliminarse él, por ello comprobar que en efecto un Robot ha entrado en la zona para
	// dar el game over

	if (ARobot* Robot = Cast<ARobot>(OtroActor)) {

		// En efecto un robot está aquí, decirle al game over que ejecute la subrutina de derrota del jugador.
		
		Cast<AGameMode_EnPartida>(UGameplayStatics::GetGameMode(this))->CongelarMundoPorDerrota(Robot);

	}

}
