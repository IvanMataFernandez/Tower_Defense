// Fill out your copyright notice in the Description page of Project Settings.


#include "Casilla.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Torre.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

float ACasilla::VolumenEfectos = 1.0f;




// Sets default values
ACasilla::ACasilla()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	// Settear el mesh
	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = this->Mesh;
	this->ComponenteDeAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Componente De Audio"));
	this->ComponenteDeAudio->SetupAttachment(this->Mesh);

}




bool ACasilla::CasillaVacia() {
  return !this->Torre;

}


void ACasilla::PonerTorre(ATorre* NuevaTorre) {
	this->Torre = NuevaTorre;
	NuevaTorre->SetOwner(this);
	this->AnimarPonerTorre();

}

void ACasilla::DestruirTorre() {

	// Se usa la TNT sobre la casilla.
	
	this->Torre->Destroy();
	this->QuitarReferenciaTorre();
	this->AnimarDestruirTorre();


}
void ACasilla::QuitarReferenciaTorre() {

	// Solo quita la referencia de la torre pero no la destruye (e.j, cuando se va a morir una torre, la propia clase se destruye pero se debe quitar su pointer)


  	this->Torre = nullptr;
	this->PonerMaterialBase(); // En blueprint, comprobar si la casilla se iluminó por un Productor, y si lo fue, apagarla y ponerla con su material original de nuevo



}





ATorre* ACasilla::ObtenerTorreEnCasilla() {
	return this->Torre;
}


void ACasilla::SetVolumenEfectosDeCasillas(float Vol, UObject* ContextoMundo) {

	ACasilla::VolumenEfectos = Vol;

	TArray<AActor*> Casillas;
    
    UGameplayStatics::GetAllActorsOfClass(ContextoMundo, ACasilla::StaticClass(), Casillas);

    for (AActor* Casilla : Casillas) {

        Cast<ACasilla>(Casilla)->ComponenteDeAudio->SetVolumeMultiplier(ACasilla::VolumenEfectos);
    }

}
