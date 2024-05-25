// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot_BombaRadar.h"
#include "Components/BoxComponent.h"


// El robot bomba radar implementa esta clase

/*

    IDs de animaciones:
   -2: Mostrar estado 2 vida (dañado)
   -1: Mostrar estado 1 vida  (muy dañado)
    0: Morir
    1: Moverse
    2: Parar de moverse
    3: Disparar laser
    4: Detonar
    5: Mover helice (activar loop)

*/


void ARobot_BombaRadar::BeginPlay() {
    Super::BeginPlay();
    Super::RealizarAnimacion(5); // Animar la rotación de helices tan pronto como spawnea en el nivel

}


// Métodos de IA:

bool ARobot_BombaRadar::SuficientesTorresEnRangoDeExplosion() {

    TArray<FOverlapResult> Resultado;
    FComponentQueryParams QueryParams;

    AreaDeExplosion->ComponentOverlapMulti(Resultado, GetWorld(), AActor::GetActorLocation(), AActor::GetActorRotation(), ECollisionChannel::ECC_GameTraceChannel6, QueryParams);
    
    
    return Resultado.Num() >= this->CantTorresParaDetonar;
}


