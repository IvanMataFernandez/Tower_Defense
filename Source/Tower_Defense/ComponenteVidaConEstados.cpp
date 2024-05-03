// Fill out your copyright notice in the Description page of Project Settings.


#include "ComponenteVidaConEstados.h"
#include "Math/UnrealMathUtility.h"
#include "Robot.h"

void UComponenteVidaConEstados::BeginPlay()
{
	Super::BeginPlay();
    this->Estado = 3;


}


void UComponenteVidaConEstados::AplicarDano(AActor* Danado, float DanoBase, const UDamageType* TipoDano, AController* Instigator, AActor* Causador) {

    Super::AplicarDano(Danado, DanoBase, TipoDano, Instigator, Causador);
    int ThresholdVida = FMath::Floor(Super::ObtenerFraccionVidaRestante() * 3)+1;

    if (ThresholdVida < this->Estado) {
        this->Estado = ThresholdVida;
        Cast<ARobot>(this->GetOwner())->RealizarAnimacion(this->Estado * -1); // TODO: Cast a Entidad si se desarrolla una torre Wall
    }
    
	


}