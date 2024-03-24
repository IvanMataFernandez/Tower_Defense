// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot_Basico.h"
#include "Math/UnrealMathUtility.h"
#include "Proyectil.h"


/*

    IDs de animaciones:
   -1: Mover ruedas (quitar loop)
    0: Morir
    1: Mover ruedas (activar loop)
    2: Disparar laser

*/

ARobot_Basico::ARobot_Basico() {

    this->MeshDisparador = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshDisparador"));
    this->SpawnProyectiles = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnProyectiles"));

    this->MeshDisparador->SetupAttachment(PosicionBase);
    this->SpawnProyectiles->SetupAttachment(this->MeshDisparador);

}


void ARobot_Basico::BeginPlay() {
    Super::BeginPlay();
}


bool ARobot_Basico::TorreEnRango() {

    FVector Start =  this->SpawnProyectiles->GetComponentLocation();
    FVector End = Start - (FVector(0,256.f+this->RangoEnCasillas*512.f,0) ); //Cada casilla son 512.f. 256.f para offsettear la casilla sobre la que está

    // Realiza el line trace y devuelve si hay hit.
    FHitResult HitResult;
  //  DrawDebugLine(GetWorld(), Start, End, FColor::Green, true);



    return GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_GameTraceChannel6); // 5 vision torre, 6 vision robot

}





void ARobot_Basico::InicializarAtaque() {

    RealizarAnimacion(-1); // Quitar el loop de animacion de movimiento de ruedas
    Super::ClearTimer();
    this->RepetirAtaque();

}

void ARobot_Basico::RepetirAtaque() {


    float Espera = this->TiempoParaAnimacionDisparo;
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ARobot_Basico::Atacar, Espera);
    GetWorld()->GetTimerManager().SetTimer(TimerFrame, Delegate, Espera, false);

    Timer = 0;
}


void ARobot_Basico::Atacar(float DeltaTime) {

    Timer = Timer + DeltaTime;

    if (Timer == this->TiempoParaAnimacionDisparo) {

        RealizarAnimacion(2); // Animar el robot para que realize el disparo
        float Espera = this->TiempoPorDisparo - Timer;

        FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ARobot_Basico::Atacar, Espera);
        GetWorld()->GetTimerManager().SetTimer(TimerFrame, Delegate, Espera, false);

    } else {
        this->Disparar();
        this->RepetirAtaque();

    }


}

void ARobot_Basico::Disparar() {
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; // Forzar al proyectil a que aparezca (por si justo se le pone una torre encima)

        AProyectil* Proyectil = AActor::GetWorld()->SpawnActor<AProyectil>(this->ClaseBlueprintProyectil, this->SpawnProyectiles->GetComponentLocation(), SpawnProyectiles->GetComponentRotation(),SpawnParams);
}
