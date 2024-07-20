// Fill out your copyright notice in the Description page of Project Settings.


#include "Torre_Producidor.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "MandoDeJugador_EnPartida.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "MandoDeIA.h"



// Las torres que son paneles solares implementan esta clase

/*

    IDs de animaciones:
    
    0: Morir
    1: Apagar paneles
    2: Encender paneles


*/




ATorre_Producidor::ATorre_Producidor() {
    this->Placas = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Placas"));
    this->Placas->SetupAttachment(RootComponent);
}

void ATorre_Producidor::BeginPlay() {
    Super::BeginPlay();
    this->MandoDeJugador = Cast<AMandoDeJugador_EnPartida>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    this->PrimeraProduccion = true;
}


void ATorre_Producidor::Click() {

    // Procesar click en la torre o en su casilla

    if (this->EnergiaDisponible) {

        // Repetir ciclo        
        Super::ClearTimer();
        Super::ProgramarTimerFinDeTareaIA(0.f);
        
        // Si está en el estado de producido, dar la energia al jugador
        this->MandoDeJugador->ActualizarEnergiaPor(this->CantidadProducida);
        

    }
}


// Métodos de IA:

void ATorre_Producidor::PrepararParaProduccion() {

    // Preparar la torre para que inicie el ciclo, se pasa al estado de empezar la animación de producir

    this->EnergiaDisponible = false;
    float TiempoParaProduccion = this->TiempoProduccionBase + (FMath::FRand() - 0.5) * 2 * this->DesviacionTiempoProduccionMax;

    if (this->PrimeraProduccion) {
        // La primera produccion se acorta para empezar a dar profit al player antes
        TiempoParaProduccion = TiempoParaProduccion / 4;
        this->PrimeraProduccion = false;

    }


    Super::ProgramarTimerFinDeTareaIA(TiempoParaProduccion);

}


void ATorre_Producidor::Producir() {

    this->RealizarAnimacion(2);
    this->EnergiaDisponible = true;

    Super::ProgramarTimerFinDeTareaIA(this->TiempoHastaQueCaducaEnergia);
}

void ATorre_Producidor::FinProduccion() {
    this->RealizarAnimacion(1);
    this->EnergiaDisponible = false;


}


