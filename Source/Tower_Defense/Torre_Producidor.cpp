// Fill out your copyright notice in the Description page of Project Settings.


#include "Torre_Producidor.h"
#include "Components/StaticMeshComponent.h"


/*

    IDs de animaciones:
    1: Producir


*/

ATorre_Producidor::ATorre_Producidor() {
    this->Placas = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Placas"));
    this->Placas->SetupAttachment(PosicionBase);
}

void ATorre_Producidor::BeginPlay() {
    Super::BeginPlay();
}

void ATorre_Producidor::PrepararTorre() {

    // Preparar la torre para que inicie el ciclo, se pasa al estado de empezar la animación de producir

    float Espera = this->TiempoParaAnimacion;
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ATorre_Producidor::Idle, Espera);
    GetWorld()->GetTimerManager().SetTimer(TimerFrame, Delegate,Espera, false);
    Timer = 0;

}
void ATorre_Producidor::Idle(float DeltaTime) {

    Timer = Timer + DeltaTime;

    if (Timer == this->TiempoParaAnimacion) {

        // Se anima la producción aquí. De aqui, pasar al estado de dar el dinero en sí

        RealizarAnimacion(1); // Animar el empiece de produccion
        
        float Espera = Ciclo - this->TiempoParaAnimacion;
        FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ATorre_Producidor::Idle, Espera);
        GetWorld()->GetTimerManager().SetTimer(TimerFrame, Delegate, Espera, false);    
    
    } else if (Timer == Ciclo) {

        // Se da el dinero aquí. De aqui volver a inicializar el ciclo de nuevo

        this->Producir();
        this->PrepararTorre();
    } 
}

void ATorre_Producidor::Producir() {
    // TODO: Dar más dinero a player here
    UE_LOG(LogTemp, Warning, TEXT("MORE MONEY!"));
}
