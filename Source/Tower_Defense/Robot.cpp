// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot.h"
#include "Math/UnrealMathUtility.h"
#include "Proyectil.h"
#include "GameMode_EnPartida.h"
#include "ConstructoraDeBlueprints.h"


/*

    IDs de animaciones:
   -1: Mover ruedas (quitar loop) 
    0: Morir
    1: Mover ruedas (activar loop) 


*/
ARobot::ARobot() {

    this->MeshDesplazador = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshDesplazador"));


    this->MeshDesplazador->SetupAttachment(PosicionBase);

}


void ARobot::BeginPlay() {
    Super::BeginPlay();
    this->Velocidad = this->VelocidadBase + (FMath::FRand() - 0.5) * 2 * this->DesviacionMaxVelocidad;
}

void ARobot::QuitarIA() {
    Super::QuitarIA();

    // En los robots, al quitar IA se debe quitar la animacion de moverse tmb
    RealizarAnimacion(-1); 

}

bool ARobot::HaMovidoEnVerticalDistanciaX(float Distancia) {

    return this->DistanciaRecorridaVertical >= Distancia;
}

void ARobot::InicializarMoverVertical(float FrameRate) {
    Super::ClearTimer();
    this->DistanciaRecorridaVertical = 0.f;
    this->Velocidad = 750;

    RealizarAnimacion(1); // Animar el robot para que se mueva (loop)

    float Espera = FrameRate;
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ARobot::MoverVertical, 1/Espera);
    GetWorld()->GetTimerManager().SetTimer(TimerFrame, Delegate, 1/Espera, true);   
}

void ARobot::MoverVertical(float DeltaTime) {
/*
    FVector Pos = this->GetActorLocation();
    Pos.Y = Pos.Y - this->Velocidad * DeltaTime; */
    FVector Pos = FVector(-this->Velocidad * DeltaTime, 0 ,0);
    this->AddActorWorldOffset(Pos);
    this->DistanciaRecorridaVertical = this->DistanciaRecorridaVertical + this->Velocidad * DeltaTime;

}


void ARobot::InicializarMover(float FrameRate) {

    Super::ClearTimer();

    RealizarAnimacion(1); // Animar el robot para que se mueva (loop)

    float Espera = FrameRate;
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ARobot::Mover, 1/Espera);
    GetWorld()->GetTimerManager().SetTimer(TimerFrame, Delegate, 1/Espera, true);    
}

void ARobot::Mover(float DeltaTime) {
/*
    FVector Pos = this->GetActorLocation();
    Pos.Y = Pos.Y - this->Velocidad * DeltaTime; */
    FVector Pos = FVector(0, - this->Velocidad * DeltaTime,0);
    this->AddActorWorldOffset(Pos);

}



void ARobot::Matar() {

    // En el caso de los robots, se debe procesar el hecho de que se ha muerto para contabilizar cuando spawnear siguiente oleada y procesar win con logic.
    int Peso = ConstructoraDeBlueprints::GetConstructoraDeBlueprints()->GetPesoDeRobot(ID);
    Cast<AGameMode_EnPartida>(GetWorld()->GetAuthGameMode())->ProcesarMuerteDeRobot(Peso, this);
    this->RealizarAnimacion(-1);
    Super::Matar();
}
