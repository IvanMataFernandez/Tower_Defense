// Fill out your copyright notice in the Description page of Project Settings.


#include "ZonaSpawnRobotPreview.h"
#include "Components/BoxComponent.h"





// Sets default values
AZonaSpawnRobotPreview::AZonaSpawnRobotPreview()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	this->ZonaDeSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("Zona de Spawn"));
	RootComponent = this->ZonaDeSpawn;

}

// Called when the game starts or when spawned
void AZonaSpawnRobotPreview::BeginPlay()
{
	Super::BeginPlay();
	this->ContadorSpawns = 0;

           

}

void AZonaSpawnRobotPreview::SpawnearRobot(int ID) {
	this->EventoSpawnearRobot(ID, this->ContadorSpawns);
	this->ContadorSpawns++;
}

