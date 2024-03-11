// Fill out your copyright notice in the Description page of Project Settings.


#include "Torre_Disparador.h"
#include "Components/SceneComponent.h"
#include "Proyectil.h"



void ATorre_Disparador::BeginPlay() {
    Super::BeginPlay();
    Disparar();
}



ATorre_Disparador::ATorre_Disparador() {

    // Super() se hace solo 

    this->SpawnProyectiles = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnProyectiles"));
    this->SpawnProyectiles->SetupAttachment(CuerpoBase);
}

void ATorre_Disparador::PrepararIdle() {

    // TODO: Empezar Idle
}
void ATorre_Disparador::Idle() {
    // NOP

}
bool ATorre_Disparador::EnRango() {
    // Calcular linetrace

    return false;
}
void ATorre_Disparador::InicializacionAtaque() {
    Timer = 0.f;
    this->TirosRestantes = this->CadenciaDeDisparo;
    // Finalizar idle

}
void ATorre_Disparador::Atacar(float DeltaTime) {
    Timer = 0;

    if (Timer == 0) {
        this->SigTiroEn = this->CooldownInicial;
    
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
    UE_LOG(LogTemp, Display, TEXT("%f"), Timer);

}

void ATorre_Disparador::Disparar() {

    // Hacer aparecer el proyectil en el spawnpoint de proyectiles. El proyectil en sí se mueve con su lógica en su código

    AActor::GetWorld()->SpawnActor<AProyectil>(this->ClaseBlueprintProyectil, this->SpawnProyectiles->GetComponentLocation(), SpawnProyectiles->GetComponentRotation());
    this->TirosRestantes--;
}
