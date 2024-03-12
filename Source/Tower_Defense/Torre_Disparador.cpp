// Fill out your copyright notice in the Description page of Project Settings.


#include "Torre_Disparador.h"
#include "Components/SceneComponent.h"
#include "Proyectil.h"
#include "TimerManager.h"

#include "DrawDebugHelpers.h"


void ATorre_Disparador::BeginPlay() {
    Super::BeginPlay();


    this->EnRango();

} 



ATorre_Disparador::ATorre_Disparador() {

    // Super() se hace solo 

    this->SpawnProyectiles = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnProyectiles"));
    this->SpawnProyectiles->SetupAttachment(CuerpoBase);
}

void ATorre_Disparador::PrepararIdle() {
    Super::ClearTimer();

    // TODO: Empezar Idle
}

bool ATorre_Disparador::EnRango() {

    FVector Start = this->GetActorLocation();
    FVector End = Start + (FVector(0,256.f+this->RangoEnCasillas*512.f,0) ); //Cada casilla son 512.f. 256.f para offsettear la casilla sobre la que está

    // Realiza el line trace y devuelve si hay hit.
    FHitResult HitResult;
    DrawDebugLine(GetWorld(), Start, End, FColor::Green, true);



    return GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_GameTraceChannel5); // 5 vision torre, 6 vision robot



}


void ATorre_Disparador::InicializacionAtaque(float FrameRate) {
    
    Timer = 0.f;
    this->TirosRestantes = this->CadenciaDeDisparo; 
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ATorre_Disparador::Atacar, 1.f/FrameRate);
    GetWorld()->GetTimerManager().SetTimer(TimerFrame, Delegate, 1.f/FrameRate, true);

}



void ATorre_Disparador::Atacar(float DeltaTime) {

    if (Timer == 0) {
        this->SigTiroEn = this->CooldownInicial;
        this->TirosRestantes = this->CadenciaDeDisparo;

    } else if (Timer > this->SigTiroEn) {
        this->Disparar();

        if (this->TirosRestantes != 0) {
            this->SigTiroEn = this->SigTiroEn + this->TiempoEntreTiros;

        
        } else {
            this->SigTiroEn = Ciclo + 1.f; // Hacer que no llegue a poder hace otro tiro porque se han acabado

        }

    } 

    if (Timer > Ciclo) {Timer = 0;}
    else {Timer = Timer + DeltaTime;}

}

void ATorre_Disparador::Disparar() {

    // Hacer aparecer el proyectil en el spawnpoint de proyectiles. El proyectil en sí se mueve con su lógica en su código

    AActor::GetWorld()->SpawnActor<AProyectil>(this->ClaseBlueprintProyectil, this->SpawnProyectiles->GetComponentLocation(), SpawnProyectiles->GetComponentRotation());
    this->TirosRestantes--;
}
