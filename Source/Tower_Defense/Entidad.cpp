// Fill out your copyright notice in the Description page of Project Settings.


#include "Entidad.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
AEntidad::AEntidad()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->PosicionBase = CreateDefaultSubobject<USceneComponent>(TEXT("PosiciónBase"));
	this->Hitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	this->CuerpoBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CuerpoBase"));
	RootComponent = this->PosicionBase;
	this->Hitbox->SetupAttachment(this->PosicionBase);
	this->CuerpoBase->SetupAttachment(this->PosicionBase);
}

// TODO: Settear BTTree en BeginPlay()





