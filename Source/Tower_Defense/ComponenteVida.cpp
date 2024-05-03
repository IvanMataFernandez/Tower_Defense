// Fill out your copyright notice in the Description page of Project Settings.


#include "ComponenteVida.h"
#include "Entidad.h"

// Sets default values for this component's properties
UComponenteVida::UComponenteVida()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false; 
	this->Vulnerable = true;

	// ...
}


// Called when the game starts
void UComponenteVida::BeginPlay()
{
	Super::BeginPlay();
	this->Vida = this->VidaMaxima;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UComponenteVida::AplicarDano); //Bindear evento de daño al método de abajo


}


void UComponenteVida::AplicarDano(AActor* Danado, float DanoBase, const UDamageType* TipoDano, AController* Instigator, AActor* Causador) {

	this->Vida -= DanoBase;

	if (this->Vida <= 0.f && this->Vulnerable) {
		Cast<AEntidad>(GetOwner())->Matar();
		this->Vulnerable = false;

	}
	


}

float UComponenteVida::ObtenerFraccionVidaRestante() {
	if (this->Vida > 0) {
		return this->Vida / this->VidaMaxima;

	} else {
		return 0.f;
	}
}





