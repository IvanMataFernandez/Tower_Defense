// Fill out your copyright notice in the Description page of Project Settings.


#include "ZonaSpawnRobotPreview.h"
#include "Components/BoxComponent.h"


// La zona invisible que hace spawnear los robots para la preview del nivel (durante la seleccion de torres)


// Sets default values
AZonaSpawnRobotPreview::AZonaSpawnRobotPreview()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	this->ZonaDeSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("Zona de Spawn de Robots"));
	RootComponent = this->ZonaDeSpawn;

}

// Called when the game starts or when spawned
void AZonaSpawnRobotPreview::BeginPlay()
{
	Super::BeginPlay();
	this->ContadorSpawns = 0;

           

}

void AZonaSpawnRobotPreview::SpawnearRobot(int ID) {
	this->EventoSpawnearRobot(ID, this->ContadorSpawns); // Va contando cuantos robots coloca y los va poniendo de tres en 3 por cada fila.
	this->ContadorSpawns++;
}


