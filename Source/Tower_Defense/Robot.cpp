// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot.h"
#include "Math/UnrealMathUtility.h"
#include "Proyectil.h"
#include "GameMode_EnPartida.h"
#include "ConstructoraDeBlueprints.h"
#include "Kismet/GameplayStatics.h"


/*

    IDs de animaciones:
    0: Morir
    1: Mover ruedas (activar loop) 
    2: Mover ruedas (quitar loop) 


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
    RealizarAnimacion(2); 

}

bool ARobot::HaMovidoEnVerticalDistanciaX(float Distancia) {

    return this->DistanciaRecorridaVertical >= Distancia;
}

void ARobot::InicializarMoverVertical() {
    Super::ClearTimer();
    this->DistanciaRecorridaVertical = 0.f;
    this->Velocidad = 750;

    RealizarAnimacion(1); // Animar el robot para que se mueva (loop)

    float DeltaTiempo = UGameplayStatics::GetWorldDeltaSeconds(this) * 1.3f;
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ARobot::MoverVertical, DeltaTiempo);
    GetWorld()->GetTimerManager().SetTimer(TimerFrame, Delegate, DeltaTiempo, true);   
}

void ARobot::MoverVertical(float DeltaTime) {
/*
    FVector Pos = this->GetActorLocation();
    Pos.Y = Pos.Y - this->Velocidad * DeltaTime; */
    FVector Pos = FVector(-this->Velocidad * DeltaTime, 0 ,0);
    this->AddActorWorldOffset(Pos);
    this->DistanciaRecorridaVertical = this->DistanciaRecorridaVertical + this->Velocidad * DeltaTime;

}


void ARobot::InicializarMover() {

    Super::ClearTimer();

    RealizarAnimacion(1); // Animar el robot para que se mueva (loop)

    float DeltaTiempo = UGameplayStatics::GetWorldDeltaSeconds(this) * 1.3f;
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ARobot::Mover, DeltaTiempo); // Actualizar move 3 de cada 4 frames aproximadamente para ahorrar recursos
    GetWorld()->GetTimerManager().SetTimer(TimerFrame, Delegate, DeltaTiempo, true);    
}

void ARobot::Mover(float DeltaTime) {
/*
    FVector Pos = this->GetActorLocation();
    Pos.Y = Pos.Y - this->Velocidad * DeltaTime; */
    FVector Pos = FVector(0, - this->Velocidad * DeltaTime,0);
    this->AddActorWorldOffset(Pos);

}

void ARobot::Parar() {
    this->Velocidad = 0;
}


void ARobot::Matar() {

    // En el caso de los robots, se debe procesar el hecho de que se ha muerto para contabilizar cuando spawnear siguiente oleada y procesar win con logic.
    int Peso = ConstructoraDeBlueprints::GetConstructoraDeBlueprints()->GetPesoDeRobot(Super::ObtenerID());
    

    // TODO: En version final este cast siempre funciona, quitar este check. Por ahora se deja para poder testear bots en stages debug sin gamemode

    if (AGameMode_EnPartida* GameMode = Cast<AGameMode_EnPartida>(GetWorld()->GetAuthGameMode())) {
        GameMode->ProcesarMuerteDeRobot(Peso, this);
    }


    this->RealizarAnimacion(2);
    Super::Matar();
}
