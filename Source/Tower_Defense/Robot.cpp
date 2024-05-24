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
    this->DistanciaRecorridaVertical = 0;
}



void ARobot::SetOleada(int Ole) {
    this->Oleada = Ole;
}


int ARobot::GetOleada() {
    return this->Oleada;
}



void ARobot::QuitarIA() {
    Super::QuitarIA();

    // En los robots, al quitar IA se debe quitar la animacion de moverse tmb
    Super::RealizarAnimacion(2); 

}

bool ARobot::HaMovidoEnVerticalDistanciaX(float Distancia) {

    return this->DistanciaRecorridaVertical >= Distancia;
}

void ARobot::InicializarMoverVertical() {
    Super::ClearTimer();
    this->DistanciaRecorridaVertical = 0.f;
    this->VelocidadActual = 750;

    Super::RealizarAnimacion(1); // Animar el robot para que se mueva (loop)
 

    float DeltaTiempo =  UGameplayStatics::GetWorldDeltaSeconds(this) * 1.3f;
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ARobot::MoverVertical, DeltaTiempo);    
    Super::ProgramarTimer(Delegate, DeltaTiempo, true);

}




void ARobot::InicializarMover() {

    Super::ClearTimer();
    Super::RealizarAnimacion(1); // Animar el robot para que se mueva (loop)

    this->VelocidadActual = this->Velocidad;




    float DeltaTiempo =  UGameplayStatics::GetWorldDeltaSeconds(this) * 1.3f;
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ARobot::Mover, DeltaTiempo); // Actualizar move 3 de cada 4 frames aproximadamente para ahorrar recursos
    Super::ProgramarTimer(Delegate, DeltaTiempo, true);

    
}

void ARobot::Mover(float DeltaTime) {

    FVector Pos = FVector(0, - this->VelocidadActual * DeltaTime,0);
    this->AddActorWorldOffset(Pos);

}

void ARobot::MoverVertical(float DeltaTime) {

    FVector Pos = FVector(-this->VelocidadActual * DeltaTime, 0 ,0);
    this->AddActorWorldOffset(Pos);
    this->DistanciaRecorridaVertical = this->DistanciaRecorridaVertical + this->VelocidadActual * DeltaTime;

}


void ARobot::Parar() {
    

    this->VelocidadActual = 0;
    Super::ClearTimer();
    Super::RealizarAnimacion(2); 

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

void ARobot::SetVelocidad(float Vel) {
    this->Velocidad = Vel;
}
