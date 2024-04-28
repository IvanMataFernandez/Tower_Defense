// Fill out your copyright notice in the Description page of Project Settings.


#include "Casilla.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Torre.h"



#include "ConstructoraDeBlueprints.h"


// Sets default values
ACasilla::ACasilla()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	// Settear el mesh
	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = this->Mesh;

}




bool ACasilla::CasillaVacia() {
  return !this->Torre;

}

void ACasilla::QuitarTorre() {

	// Pre: Casilla con Torre

	this->Torre->QuitarTorre();
	
}



void ACasilla::LiberarCasilla() {
  // This->Torre Llama aquí para quitarse de la casilla

  this->Torre->SetOwner(nullptr);
  this->Torre = nullptr;

}


ATorre* ACasilla::ObtenerTorreEnCasilla() {
	return this->Torre;
}
