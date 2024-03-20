// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot_BombaRadar.h"
#include "Components/BoxComponent.h"


/*

    IDs de animaciones:
   -1: Mover ruedas (quitar loop) y mover helice (quitar loop)
    0: Mover ruedas (activar loop) y 
    1: Disparar laser
    2: Detonar
    3: Mover helice (activar loop)

*/


void ARobot_BombaRadar::BeginPlay() {
    Super::BeginPlay();
    RealizarAnimacion(3);

}

bool ARobot_BombaRadar::SuficientesTorresEnRangoDeExplosion() {

    TArray<FOverlapResult> Resultado;
    FComponentQueryParams QueryParams;

    AreaDeExplosion->ComponentOverlapMulti(Resultado, GetWorld(), AActor::GetActorLocation(), AActor::GetActorRotation(), ECollisionChannel::ECC_GameTraceChannel6, QueryParams);
    
    
    return Resultado.Num() >= this->CantTorresParaDetonar;
}


