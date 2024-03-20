// Fill out your copyright notice in the Description page of Project Settings.


#include "ZonaSpawnRobot.h"
#include "Components/BoxComponent.h"





// Sets default values
AZonaSpawnRobot::AZonaSpawnRobot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	this->ZonaDeSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("Zona de Spawn"));
	RootComponent = this->ZonaDeSpawn;

}

// Called when the game starts or when spawned
void AZonaSpawnRobot::BeginPlay()
{
	Super::BeginPlay();
	FVector TamañoDeArea = this->ZonaDeSpawn->GetScaledBoxExtent();
	float LongX = TamañoDeArea.X;


	for (int i = 0; i != 5; i++) {
		PosicionesDeSpawn.Add(LongX * (0.4 * i - 0.8));
	}

           

}

