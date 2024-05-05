// Fill out your copyright notice in the Description page of Project Settings.


#include "Torre_Producidor.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "MandoDeJugador_EnPartida.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "MandoDeIA.h"

/*

    IDs de animaciones:
    
    0: Morir
    1: Apagar paneles
    2: Encender paneles


*/


  //  this->Velocidad = this->VelocidadBase + (FMath::FRand() - 0.5) * 2 * this->DesviacionMaxVelocidad;


ATorre_Producidor::ATorre_Producidor() {
    this->Placas = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Placas"));
    this->Placas->SetupAttachment(PosicionBase);
}

void ATorre_Producidor::BeginPlay() {
    Super::BeginPlay();
    this->MandoDeJugador = Cast<AMandoDeJugador_EnPartida>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    this->MandoDeIA = Cast<AMandoDeIA>(this->GetController());
}

void ATorre_Producidor::PrepararParaProduccion() {

    // Preparar la torre para que inicie el ciclo, se pasa al estado de empezar la animación de producir

    this->EnergiaDisponible = false;
    float TiempoParaProduccion = this->TiempoProduccionBase + (FMath::FRand() - 0.5) * 2 * this->DesviacionTiempoProduccionMax;
    GetWorld()->GetTimerManager().SetTimer(TimerFrame, this->MandoDeIA, &AMandoDeIA::AcabarTareaActual, TiempoParaProduccion, false);               


}


void ATorre_Producidor::Producir() {

    this->RealizarAnimacion(2);
    this->EnergiaDisponible = true;
    GetWorld()->GetTimerManager().SetTimer(TimerFrame, this->MandoDeIA, &AMandoDeIA::AcabarTareaActual, this->TiempoHastaQueCaducaEnergia, false);               

}

void ATorre_Producidor::FinProduccion() {
    this->RealizarAnimacion(1);
    this->EnergiaDisponible = false;
   // this->MandoDeIA->AcabarTareaActual();


}

void ATorre_Producidor::Click() {

    if (this->EnergiaDisponible) {
        // DAR MONEY!
        this->MandoDeJugador->IncrementarEnergia(this->CantidadProducida);

        // Repetir ciclo        
        GetWorld()->GetTimerManager().ClearTimer(TimerFrame);
        this->MandoDeIA->AcabarTareaActual();
    }
}

