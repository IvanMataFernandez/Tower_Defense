// Fill out your copyright notice in the Description page of Project Settings.


#include "Casilla.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Torre.h"
#include "Materials/Material.h"





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
void ACasilla::DestruirTorre() {

	// Se quiere quitar la referencia y destruir el actor (e.j, cuando se usa la TNT para quitar la torre y se skippea la animacion de muerte)
	
	this->Torre->Destroy();
	this->QuitarReferenciaTorre();


}
void ACasilla::QuitarReferenciaTorre() {

	// Solo quita la referencia de la torre pero no la destruye (e.j, cuando se va a morir una torre, la propia clase se destruye pero se debe quitar su pointer)




  	this->Torre = nullptr;
	this->PonerMaterialBase(); // En blueprint, comprobar si la casilla se iluminó por un Productor, y si lo fue, apagarla y ponerla con su material original de nuevo



}





ATorre* ACasilla::ObtenerTorreEnCasilla() {
	return this->Torre;
}
