// Fill out your copyright notice in the Description page of Project Settings.


#include "Torre_UsoInstantaneo.h"
#include "Components/BoxComponent.h"



ATorre_UsoInstantaneo::ATorre_UsoInstantaneo() {

    // super() se hace solo
    this->ZonaDeAfecto = CreateDefaultSubobject<UBoxComponent>(TEXT("ZonaDeAfecto"));
    this->ZonaDeAfecto->SetupAttachment(PosicionBase);
}


void ATorre_UsoInstantaneo::BeginPlay() {
    Super::BeginPlay();
    Timer = 0;
}

void ATorre_UsoInstantaneo::HacerFuncion(float DeltaTime) {

    if (Timer > this->TiempoParaAnimacion) {/* Hacer animacion*/}
    else if (Timer > Ciclo) {
        this->Activar();
    }
    Timer = Timer + DeltaTime;
}


void ATorre_UsoInstantaneo::Activar() {
    // Em principio dañar aquí, pero si se quieren hacer otras funciones en un area, entonces hacer esto Virtual y heredar de esta clase

}