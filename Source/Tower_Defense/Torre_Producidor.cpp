// Fill out your copyright notice in the Description page of Project Settings.


#include "Torre_Producidor.h"
#include "Components/StaticMeshComponent.h"


ATorre_Producidor::ATorre_Producidor() {
    this->Placas = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Placas"));
    this->Placas->SetupAttachment(PosicionBase);
}

void ATorre_Producidor::BeginPlay() {
    Super::BeginPlay();
    Timer = 0;
}


void ATorre_Producidor::Idle(float DeltaTime) {

    if (Timer > this->TiempoParaAnimacion) {/* Animar aquí*/}
    
    if (Timer > Ciclo) {
        this->Producir();
        Timer = 0;
    } else {
        Timer = Timer + DeltaTime;
    }
}

void ATorre_Producidor::Producir() {
    // Dar más dinero a player here
}
