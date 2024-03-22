// Fill out your copyright notice in the Description page of Project Settings.


#include "Torre_Producidor.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "MandoDeJugador_EnPartida.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

/*

    IDs de animaciones:
    0: Apagar paneles
    1: Encender paneles


*/


  //  this->Velocidad = this->VelocidadBase + (FMath::FRand() - 0.5) * 2 * this->DesviacionMaxVelocidad;


ATorre_Producidor::ATorre_Producidor() {
    this->Placas = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Placas"));
    this->Placas->SetupAttachment(PosicionBase);
}

void ATorre_Producidor::BeginPlay() {
    Super::BeginPlay();
    this->MandoDeJugador = Cast<AMandoDeJugador_EnPartida>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void ATorre_Producidor::PrepararTorre() {

    // Preparar la torre para que inicie el ciclo, se pasa al estado de empezar la animación de producir
     RealizarAnimacion(0); // Animar el apague de produccion

    this->EnergiaDisponible = false;
    float TiempoParaProduccion = this->TiempoProduccionBase + (FMath::FRand() - 0.5) * 2 * this->DesviacionTiempoProduccionMax;
    GetWorld()->GetTimerManager().SetTimer(TimerFrame, this, &ATorre_Producidor::Producir,TiempoParaProduccion, false);               

}


void ATorre_Producidor::Producir() {
    RealizarAnimacion(1); // Animar el empiece de produccion

    this->EnergiaDisponible = true;
    GetWorld()->GetTimerManager().SetTimer(TimerFrame, this, &ATorre_Producidor::PrepararTorre,this->TiempoHastaQueCaducaEnergia, false);               

}

void ATorre_Producidor::Click() {

    if (this->EnergiaDisponible) {
        // DAR MONEY!
        this->MandoDeJugador->IncrementarEnergia(this->CantidadProducida);

        // Repetir ciclo        
        GetWorld()->GetTimerManager().ClearTimer(TimerFrame);
        this->PrepararTorre();
    }
}
