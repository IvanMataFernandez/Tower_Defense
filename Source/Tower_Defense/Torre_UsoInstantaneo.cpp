// Fill out your copyright notice in the Description page of Project Settings.


#include "Torre_UsoInstantaneo.h"
#include "Components/BoxComponent.h"
#include "ComponenteVida.h"
#include "Kismet/GameplayStatics.h"


ATorre_UsoInstantaneo::ATorre_UsoInstantaneo() {

    // super() se hace solo
    this->ZonaDeAfecto = CreateDefaultSubobject<UBoxComponent>(TEXT("ZonaDeAfecto"));
    this->ZonaDeAfecto->SetupAttachment(PosicionBase);
}


void ATorre_UsoInstantaneo::BeginPlay() {
    Super::BeginPlay();

    // Las torres de uso instantaneo NO PUEDEN MORIR A ROBOTS. Estas se matan ellas mismas tras hacer su función

    UComponenteVida* ComponenteVida = FindComponentByClass<UComponenteVida>();

    if (ComponenteVida) {
        
        ComponenteVida->Vulnerable = false;
    } 
}

void ATorre_UsoInstantaneo::InicializacionFuncion() {





    float Espera = this->Ciclo;
    GetWorld()->GetTimerManager().SetTimer(TimerFrame, this, &ATorre_UsoInstantaneo::HacerFuncion,Espera, false);
    RealizarAnimacion(1);

}

void ATorre_UsoInstantaneo::HacerFuncion() {
    this->Activar();

}


void ATorre_UsoInstantaneo::Activar() {
    // Em principio dañar aquí, pero si se quieren hacer otras funciones en un area, entonces hacer esto Virtual y heredar de esta clase

    // Por defecto hace BOOM! Pero se puede heredar de esta clase e implementar este metodo despues si se necesitan usos instantaneos que no hagan daño.
    // Si hacen daño con un efecto añadido, se puede considerar heredar de aqui. Para ello dividir buscar targets y dañar en dos metodos aparte


    // Encontrar targets y dañarlos

    TArray<FOverlapResult> Resultado;
    FComponentQueryParams QueryParams;

    // Para que encuentre target debe primero encontrar el trace (usando el canal 5) y luego el campo y el target deben ser al menos overlappeables respecto a colision fisica
    this->ZonaDeAfecto->ComponentOverlapMulti(Resultado, GetWorld(), AActor::GetActorLocation(), AActor::GetActorRotation(), ECollisionChannel::ECC_GameTraceChannel5, QueryParams);



    for (FOverlapResult Objeto : Resultado) {
        AActor* Actor = Objeto.GetActor();
	    UGameplayStatics::ApplyDamage(Actor, this->DanoDeExplosion, nullptr, this, UDamageType::StaticClass());




    }




    Super::Matar(); // La torre desaparece tras hacer su función

}