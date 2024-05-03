// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot_BombaRadar.h"
#include "Components/BoxComponent.h"


/*

    IDs de animaciones:
   -2: Mostrar estado 2 vida
   -1: Mostrar estado 1 vida 
    0: Morir
    1: Mover ruedas (activar loop) 
    2: Mover ruedas (quitar loop) 
    3: Disparar laser
    4: Detonar
    5: Mover helice (activar loop)

*/


void ARobot_BombaRadar::BeginPlay() {
    Super::BeginPlay();
    RealizarAnimacion(5);

}

bool ARobot_BombaRadar::SuficientesTorresEnRangoDeExplosion() {

    TArray<FOverlapResult> Resultado;
    FComponentQueryParams QueryParams;

    AreaDeExplosion->ComponentOverlapMulti(Resultado, GetWorld(), AActor::GetActorLocation(), AActor::GetActorRotation(), ECollisionChannel::ECC_GameTraceChannel6, QueryParams);
    
    
    return Resultado.Num() >= this->CantTorresParaDetonar;
}


