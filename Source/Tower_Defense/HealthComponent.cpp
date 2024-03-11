// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Entidad.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; // TODO: Probar con esto a False

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	this->Vida = this->VidaMaxima;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::AplicarDano); //Bindear evento de daño al método de abajo



}


void UHealthComponent::AplicarDano(AActor* Danado, float DanoBase, const UDamageType* TipoDano, AController* Instigator, AActor* Causador) {

	this->Vida -= DanoBase;

	if (this->Vida <= 0.f) {
		Cast<AEntidad>(GetOwner())->Matar();
	}


}



