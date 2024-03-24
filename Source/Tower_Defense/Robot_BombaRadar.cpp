// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot_BombaRadar.h"
#include "Components/BoxComponent.h"


/*

    IDs de animaciones:
   -1: Mover ruedas (quitar loop) y mover helice (quitar loop)
    0: Morir
    1: Mover ruedas (activar loop) 
    2: Disparar laser
    3: Detonar
    4: Mover helice (activar loop)

*/


void ARobot_BombaRadar::BeginPlay() {
    Super::BeginPlay();
    RealizarAnimacion(4);

}

bool ARobot_BombaRadar::SuficientesTorresEnRangoDeExplosion() {

    TArray<FOverlapResult> Resultado;
    FComponentQueryParams QueryParams;

    AreaDeExplosion->ComponentOverlapMulti(Resultado, GetWorld(), AActor::GetActorLocation(), AActor::GetActorRotation(), ECollisionChannel::ECC_GameTraceChannel6, QueryParams);
    
    
    return Resultado.Num() >= this->CantTorresParaDetonar;
}


