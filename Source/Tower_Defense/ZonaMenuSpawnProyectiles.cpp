// Fill out your copyright notice in the Description page of Project Settings.

#include "ZonaMenuSpawnProyectiles.h"
#include "Math/UnrealMathUtility.h"


// Es una zona invisible que se usa en el menú principal para que aparezcan proyectiles yendo hacia los lados y hacer
// la pantalla del menú más dinámica

AZonaMenuSpawnProyectiles::AZonaMenuSpawnProyectiles()
{

	PrimaryActorTick.bCanEverTick = false;
	this->ZonaDeSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("Zona de Spawn"));
	RootComponent = this->ZonaDeSpawn;
}

// Called when the game starts or when spawned
void AZonaMenuSpawnProyectiles::BeginPlay()
{
	// Obtener el tamaño de la caja
	Super::BeginPlay();
	this->SizeX =  this->ZonaDeSpawn->GetScaledBoxExtent().X;
	this->SizeZ =  this->ZonaDeSpawn->GetScaledBoxExtent().Z;

	GetWorld()->GetTimerManager().SetTimer(this->Timer, this, &AZonaMenuSpawnProyectiles::ProgramarSpawn, 1/FrecuenciaSpawnPorSegundo, true);
}



void AZonaMenuSpawnProyectiles::ProgramarSpawn() {


	 // Spawnear proyectil cada X Tiempo
	 this->SpawnProyectil(this->SizeX * 2.f * (FMath::FRand()-0.5f), this->SizeZ * 2.f * (FMath::FRand()-0.5f));
    

}	
void AZonaMenuSpawnProyectiles::DetenerSpawns() {
	GetWorld()->GetTimerManager().ClearTimer(this->Timer);
}
