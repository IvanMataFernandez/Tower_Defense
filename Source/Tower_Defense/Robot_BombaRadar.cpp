// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot_BombaRadar.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


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

void ARobot_BombaRadar::ForzarExplosion() {
    
    // Esta función se llama si el robot bomba radar desea estallar ya incluso cuando no ha perdido todos sus puntos de vida
    // El bot solo puede estallar si no tiene vida restante (funcionalidad heredada de robot bomba)
    // Para forzar la explosión sencillamente hacer que se cause inf daño interno para que pierda toda su vida y estalle por eso 


	UGameplayStatics::ApplyDamage(this, 99999.f, nullptr, this, UDamageType::StaticClass());

}
