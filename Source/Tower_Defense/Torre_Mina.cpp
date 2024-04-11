// Fill out your copyright notice in the Description page of Project Settings.


#include "Torre_Mina.h"
#include "MandoDeIA.h"
#include "ComponenteVida.h"
#include "Components/BoxComponent.h"


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


void ATorre_Mina::Prepararse() {

	// Esperar tiempodepreparacion para marcar la tarea de preparar como completada en su BT. La siguiente tarea será pasar al estado Preparado

	AMandoDeIA* MandoDeIA = Cast<AMandoDeIA> (this->GetController());
	GetWorld()->GetTimerManager().SetTimer(TimerFrame, MandoDeIA, &AMandoDeIA::AcabarTareaActual, this->TiempoDePreparacion, false);               


}

void ATorre_Mina::Preparado() {

	// Invisibilizar la mina y hacerla invencible, para esperar a que un bot pise en ella para detonarla
	this->RealizarAnimacion(2);

	Super::Invisibilizar();
	
    UComponenteVida* ComponenteVida = FindComponentByClass<UComponenteVida>();
	ComponenteVida->Vulnerable = false;

	// Activar el trigger para cuando un bot pase por encima detone

	this->ZonaTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATorre_Mina::EnContacto);


}


void ATorre_Mina::EnContacto(UPrimitiveComponent* ComponenteNuestro, AActor* OtroActor, UPrimitiveComponent* OtroComponente, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Resultado) {
 	
	
	// Un bot ha pasado por encima, completar la tarea actual. El siguiente paso es detonar que está ya implementado en Torre_UsoUnico

	Cast<AMandoDeIA> (this->GetController())->AcabarTareaActual();

}
