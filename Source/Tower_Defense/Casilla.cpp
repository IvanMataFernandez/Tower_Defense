// Fill out your copyright notice in the Description page of Project Settings.


#include "Casilla.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Torre.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"



// Una casilla es una posición en el nivel en el que se puede colocar una torre. Están en formación 5x9 (5 filas, 9 columnas).
// Los robots se aproximan por la derecha y siempre viajan sobre una misma fila



float ACasilla::VolumenEfectos = 1.0f;




ACasilla::ACasilla()
{
	PrimaryActorTick.bCanEverTick = false;


	// Settear componentes
	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	this->ComponenteDeAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Componente De Audio"));
	this->CampoAntiRobot = CreateDefaultSubobject<UBoxComponent>(TEXT("CampoAntiRobot"));

	RootComponent = this->Mesh;
	this->ComponenteDeAudio->SetupAttachment(this->Mesh);
	this->CampoAntiRobot->SetupAttachment(this->Mesh);



}




bool ACasilla::CasillaVacia() {return !this->Torre;}




void ACasilla::PonerTorre(ATorre* NuevaTorre) {

	// Pre: Se ha instanciado NuevaTorre sobre esta casilla
	// Post: Se vincula da Owner de la Torre a la Casilla y se settea el atributo de la Torre que aloja la casilla. Además, se crean efectos (sonido) por pantalla

	this->Torre = NuevaTorre; // Settear relación Casilla -> Torre
	NuevaTorre->SetOwner(this); // Settear relación Torre -> Casilla
	this->AnimarPonerTorre(); // Llamar a BP para que haga los efectos visuales de colocar la torre (por ahora solo hace sonidos)

}

void ACasilla::DestruirTorre() {

	// Se usa la TNT sobre la casilla, eliminando así la torre y bypasseando cualquier animación de muerte o detonación de la torre a quitar
	
	this->Torre->Destroy(); // Destruir el actor (bypassea el método de matar, omitiendo así cualquier animación)
	this->QuitarReferenciaTorre(); // Quitar la relacion Casilla -> Torre
	this->AnimarDestruirTorre(); // Poner efectos visuales de una explosión en la casilla usando Blueprints


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


bool ACasilla::RobotPisandoFinalDeCasilla() {
	

	// Buscar si hay una hitbox de robot overlappeando el campo antirobot

    TArray<FOverlapResult> Resultado;
    FComponentQueryParams QueryParams;

    this->CampoAntiRobot->ComponentOverlapMulti(Resultado, GetWorld(), AActor::GetActorLocation(), AActor::GetActorRotation(), ECollisionChannel::ECC_GameTraceChannel5, QueryParams);

	return Resultado.Num() > 0;


}
