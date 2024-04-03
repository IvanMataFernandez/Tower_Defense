// Fill out your copyright notice in the Description page of Project Settings.


#include "Entidad.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "MandoDeIA.h"
#include "Torre.h"
#include "ComponenteVida.h"

// Sets default values
AEntidad::AEntidad()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // Acciones controladas por BT, no requiere tick ninguna entidad
	this->PosicionBase = CreateDefaultSubobject<USceneComponent>(TEXT("PosiciónBase"));
	this->Hitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	this->CuerpoBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CuerpoBase"));
	RootComponent = this->PosicionBase;
	this->Hitbox->SetupAttachment(this->PosicionBase);
	this->CuerpoBase->SetupAttachment(this->PosicionBase);



}




void AEntidad::Matar() {
	// Se llama a este método cuando vida = 0
	// Quitar BT de la clase porque se va a morir



	// RealizarAnimacion(int Animacion)

	AMandoDeIA* IA = Cast<AMandoDeIA>(this->GetController());

	if (IA) {
		this->DetachFromControllerPendingDestroy();
		IA->Destroy();
	}
	this->ClearTimer(); // Apagar el timer de la clase
	this->Hitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Quitar hitbox para que los enemigos ignoren a esta entidad
	this->RealizarAnimacion(0);
	GetWorld()->GetTimerManager().SetTimer(TimerFrame, this, &AEntidad::Destruir,this->TiempoDeAnimacionDeMuerte, false);    

}


void AEntidad::Destruir() {
	AActor::Destroy(); // Eliminar la entidad (Robot o Torre, debe eliminarse igual)
}

void AEntidad::BeginPlay() {
	Super::BeginPlay();

	// Dar controller de IA

	AIControllerClass = AMandoDeIA::StaticClass();

	if (!this->Tags.Contains("NoIA")) {

		// Asignar IA ya que no contiene NoIA

		AMandoDeIA* Mando = GetWorld()->SpawnActor<AMandoDeIA>();
		Mando->SettearIA(this->ID, Cast<ATorre>(this) != nullptr); // Decirle que clase es para settear el Behavior Tree adecuado
		Mando->Possess(this);

	} else {

		// Si no tienen IA, no deberían contabilizar vida. Entidades sin IA se usan como decoración o mostrar info.

		UComponenteVida* ComponenteVida = FindComponentByClass<UComponenteVida>();

		if (ComponenteVida) {
			ComponenteVida->Vulnerable = false;
		} 
	}




}

void AEntidad::ClearTimer() {



           

    GetWorld()->GetTimerManager().ClearTimer(this->TimerFrame);
            

}



/*
// PARA OBTENER COMPONENTES C++ AÑADIDOS EN BLUEPRINT (LOS ACTORCOMPONENT NON SCENECOMPONENT)

UHealthComponent* HealthComponent = FindComponentByClass<UHealthComponent>();
if (HealthComponent)
{
    // Has encontrado el componente, puedes hacer lo que necesites con él
    // Por ejemplo, puedes cambiar la malla asignada al componente de la siguiente manera:
    HealthComponent->Hello();
} 
*/