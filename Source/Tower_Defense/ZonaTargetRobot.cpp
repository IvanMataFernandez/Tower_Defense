// Fill out your copyright notice in the Description page of Project Settings.


#include "ZonaTargetRobot.h"
#include "Components/BoxComponent.h"
#include "Robot.h"
#include "GameMode_EnPartida.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AZonaTargetRobot::AZonaTargetRobot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

	// Puede ser posible que un proyectil triggeé este evento, para ello comprobar que en efecto un Robot ha entrado en la zona

	if (ARobot* Robot = Cast<ARobot>(OtroActor)) {

		UE_LOG(LogTemp, Warning, TEXT("GAME OVER!")); 

		Cast<AGameMode_EnPartida>(UGameplayStatics::GetGameMode(this))->CongelarMundoPorDerrota(Robot);

	}

}
