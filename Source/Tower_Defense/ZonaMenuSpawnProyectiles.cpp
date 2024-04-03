// Fill out your copyright notice in the Description page of Project Settings.

#include "ZonaMenuSpawnProyectiles.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AZonaMenuSpawnProyectiles::AZonaMenuSpawnProyectiles()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	this->ZonaDeSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("Zona de Spawn"));
	RootComponent = this->ZonaDeSpawn;
}

// Called when the game starts or when spawned
void AZonaMenuSpawnProyectiles::BeginPlay()
{
	Super::BeginPlay();
	this->SizeX =  this->ZonaDeSpawn->GetScaledBoxExtent().X;
	this->SizeZ =  this->ZonaDeSpawn->GetScaledBoxExtent().Z;
	this->ProgramarSpawn();
}



void AZonaMenuSpawnProyectiles::ProgramarSpawn() {
	UE_LOG(LogTemp, Warning, TEXT("HELLO"));
    
	FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &AZonaMenuSpawnProyectiles::SpawnProyectil, this->SizeX * 2.f * (FMath::FRand()-0.5f), this->SizeZ * 2.f * (FMath::FRand()-0.5f));
	FTimerHandle Timer;
    GetWorld()->GetTimerManager().SetTimer(Timer, Delegate, 1/FrecuenciaSpawnPorSegundo, false);

}