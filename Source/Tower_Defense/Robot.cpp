// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot.h"
#include "Math/UnrealMathUtility.h"
#include "Proyectil.h"



ARobot::ARobot() {

    this->MeshDesplazador = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshDesplazador"));


    this->MeshDesplazador->SetupAttachment(PosicionBase);

}


void ARobot::BeginPlay() {
    Super::BeginPlay();
    this->Velocidad = this->VelocidadBase + (FMath::FRand() - 0.5) * 2 * this->DesviacionMaxVelocidad;

}




void ARobot::InicializarMover(float FrameRate) {

    Super::ClearTimer();

    RealizarAnimacion(0); // Animar el robot para que se mueva (loop)

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

    Super::Matar();
}
