// Fill out your copyright notice in the Description page of Project Settings.


#include "Torre_Mina.h"
#include "MandoDeIA.h"
#include "Components/BoxComponent.h"


// La torre mina implementa esta clase

/*


    IDs de animaciones:

    0: Morir
    1: Activar Detonación
	2: Preparado

*/



// Sets default values
ATorre_Mina::ATorre_Mina()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	this->ZonaTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("ZonaTrigger"));
	this->ZonaTrigger->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATorre_Mina::BeginPlay()
{
	Super::BeginPlay();
	
}



void ATorre_Mina::EnContacto(UPrimitiveComponent* ComponenteNuestro, AActor* OtroActor, UPrimitiveComponent* OtroComponente, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Resultado) {
 	
	
	// Un bot ha pasado por encima, completar la tarea actual. El siguiente paso es detonar que está ya implementado en Torre_UsoUnico
	
	this->ZonaTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Quitar la hitbox de deteccion de bots encima para que no intente detonar otra vez

	Cast<AMandoDeIA> (this->GetController())->AcabarTareaActual();

}


// Métodos de IA:

void ATorre_Mina::Prepararse() {

	// Esperar tiempodepreparacion para marcar la tarea de preparar como completada en su BT. La siguiente tarea será pasar al estado Preparado


	Super::ProgramarTimerFinDeTareaIA(this->TiempoDePreparacion); 

}

void ATorre_Mina::Preparado() {

	// Invisibilizar la mina y quitarle la colision de daño, para esperar a que un bot pise en ella para detonarla
	this->RealizarAnimacion(2);

	Super::Invisibilizar();
	Super::DesactivarHitbox();
	
 	Super::SetVulnerable(false);

	// Activar el trigger para cuando un bot pase por encima detone

	this->ZonaTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATorre_Mina::EnContacto);


}


