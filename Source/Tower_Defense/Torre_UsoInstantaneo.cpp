// Fill out your copyright notice in the Description page of Project Settings.


#include "Torre_UsoInstantaneo.h"
#include "Components/BoxComponent.h"
#include "HealthComponent.h"


ATorre_UsoInstantaneo::ATorre_UsoInstantaneo() {

    // super() se hace solo
    this->ZonaDeAfecto = CreateDefaultSubobject<UBoxComponent>(TEXT("ZonaDeAfecto"));
    this->ZonaDeAfecto->SetupAttachment(PosicionBase);
}


void ATorre_UsoInstantaneo::BeginPlay() {
    Super::BeginPlay();

    // Las torres de uso instantaneo NO PUEDEN MORIR A ROBOTS. Estas se matan ellas mismas tras hacer su función

    UHealthComponent* HealthComponent = FindComponentByClass<UHealthComponent>();

    if (HealthComponent) {
        
        HealthComponent->Vulnerable = false;
    } 
}

void ATorre_UsoInstantaneo::InicializacionFuncion() {





    float Espera = this->TiempoParaAnimacion;
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ATorre_UsoInstantaneo::HacerFuncion, Espera);
    GetWorld()->GetTimerManager().SetTimer(TimerFrame, Delegate,Espera, false);
    Timer = 0;
}

void ATorre_UsoInstantaneo::HacerFuncion(float DeltaTime) {
    
    Timer = Timer + DeltaTime;

    if (Timer == this->TiempoParaAnimacion) {
        /* Hacer animacion*/
    
        float Espera = Ciclo - Timer;
        FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ATorre_UsoInstantaneo::HacerFuncion, Espera);
        GetWorld()->GetTimerManager().SetTimer(TimerFrame, Delegate,Espera, false);



    } else if (Timer == Ciclo) {
        this->Activar();
    }
}


void ATorre_UsoInstantaneo::Activar() {
    // Em principio dañar aquí, pero si se quieren hacer otras funciones en un area, entonces hacer esto Virtual y heredar de esta clase

    // Explode or do w/e

    Super::Matar(); // La torre desaparece tras hacer su función

}