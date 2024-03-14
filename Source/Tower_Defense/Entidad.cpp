// Fill out your copyright notice in the Description page of Project Settings.


#include "Entidad.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "MandoDeIA.h"

// Sets default values
AEntidad::AEntidad()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->PosicionBase = CreateDefaultSubobject<USceneComponent>(TEXT("PosiciónBase"));
	this->Hitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	this->CuerpoBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CuerpoBase"));
	RootComponent = this->PosicionBase;
	this->Hitbox->SetupAttachment(this->PosicionBase);
	this->CuerpoBase->SetupAttachment(this->PosicionBase);



}




void AEntidad::Matar() {
	// Se llama a este método cuando vida = 0
	this->ClearTimer(); // Apagar el timer de la clase
	AActor::Destroy(); // Eliminar la entidad (Robot o Torre, debe eliminarse igual)

}



void AEntidad::BeginPlay() {
	Super::BeginPlay();

	int A = 8;
	// Dar controller de IA

	AIControllerClass = AMandoDeIA::StaticClass();
	AMandoDeIA* Mando = GetWorld()->SpawnActor<AMandoDeIA>();
	Mando->SettearIA(this->ID); // Decirle que clase es para settear el Behavior Tree adecuado
    Mando->Possess(this);


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