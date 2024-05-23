// Fill out your copyright notice in the Description page of Project Settings.


#include "Entidad.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "MandoDeIA.h"
#include "Torre.h"
#include "ComponenteVida.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"


float AEntidad::VolumenEfectos = 1.0f;


// Sets default values
AEntidad::AEntidad()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // Acciones controladas por BT, no requiere tick ninguna entidad
	this->PosicionBase = CreateDefaultSubobject<USceneComponent>(TEXT("PosiciónBase"));
	this->Hitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	this->CuerpoBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CuerpoBase"));
	this->ComponenteDeAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Componente De Audio"));

	RootComponent = this->PosicionBase;
	this->Hitbox->SetupAttachment(this->PosicionBase);
	this->CuerpoBase->SetupAttachment(this->PosicionBase);
	this->ComponenteDeAudio->SetupAttachment(this->PosicionBase);

}


void AEntidad::ProgramarTimer(FTimerDelegate Delegate, float TiempoDeEspera, bool EnBucle) {
    GetWorld()->GetTimerManager().SetTimer(TimerFrame, Delegate, TiempoDeEspera, EnBucle);
}


void AEntidad::ProgramarTimerFinDeTareaIA(float TiempoEspera) {

	if (TiempoEspera > 0.01f) {
		FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this->MandoDeIA, &AMandoDeIA::AcabarTareaActual);    
		this->ProgramarTimer(Delegate, TiempoEspera, false);
	
	} else {
		this->MandoDeIA->AcabarTareaActual();
	}
	

}


uint8 AEntidad::ObtenerID() {
	return this->ID;
}

void AEntidad::SetVolumenEfectosDeEntidades(float Vol, UObject* Contexto) {
	AEntidad::VolumenEfectos = Vol;

	TArray<AActor*> Entidades;
    
    UGameplayStatics::GetAllActorsOfClass(Contexto, AEntidad::StaticClass(), Entidades);

    for (AActor* Entidad : Entidades) {

        Cast<AEntidad>(Entidad)->ComponenteDeAudio->SetVolumeMultiplier(AEntidad::VolumenEfectos);
    }


}







void AEntidad::Invisibilizar() {

	// Settear Trace Responses de Visto por Robot y Torre a ignore, para que las entidades no puedan targettearlo

	this->Hitbox->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel5, ECollisionResponse::ECR_Ignore);
	this->Hitbox->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel6, ECollisionResponse::ECR_Ignore);

}


void AEntidad::DesactivarHitbox() {
	this->Hitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Quitar hitbox para que los enemigos ignoren a esta entidad y los proyectiles la sobrepasen

}

void AEntidad::Matar() {
	// Se llama a este método cuando vida = 0
	// Quitar BT de la clase porque se va a morir

	this->QuitarIA();
	this->DesactivarHitbox();
	// Comprobar si la entidad tenia componente de vida y es vulnerable, si lo es, entonces animar su muerte
	// Si no cumple la condicion, la unidad se habria automatado y no tiene sentido animar esa muerte (ej, matarse tras haber realizado una explosion)

	UComponenteVida* ComponenteVida = FindComponentByClass<UComponenteVida>();

	if (ComponenteVida && ComponenteVida->EsVulnerable()) {
		this->RealizarAnimacion(0);
		GetWorld()->GetTimerManager().SetTimer(TimerFrame, this, &AEntidad::Destruir,this->TiempoDeAnimacionDeMuerte, false);    

	} else {
		this->AutoDestruir(); // Es esencialmente Destroy(), pero con un timer de espera potencialmente distinto segun la clase antes de quitarse
	}




}

void AEntidad::QuitarIA() {
	AMandoDeIA* IA = Cast<AMandoDeIA>(this->GetController());

	if (IA) {
		this->DetachFromControllerPendingDestroy();
		IA->Destroy();
	}


	this->ClearTimer(); // Apagar el timer de la clase

}

void AEntidad::PausarEntidad() {


	// Pausar IA

	AMandoDeIA* IA = Cast<AMandoDeIA>(this->GetController());

	if (IA && IA->TieneIA()) {
		IA->ActivarIA(false);
		GetWorld()->GetTimerManager().ClearTimer(TimerFrame);
	}

	// Detener animaciones

	this->DestruirAnimaciones();

}


void AEntidad::DespausarEntidad() {

	AMandoDeIA* IA = Cast<AMandoDeIA>(this->GetController());

	if (IA) {
		IA->ActivarIA(true);
	}

	// La IA activa las animaciones de nuevo

}

void AEntidad::Destruir() {
	AActor::Destroy(); // Eliminar la entidad (Robot o Torre, debe eliminarse igual)
}

void AEntidad::AutoDestruir() {
	

	/* Reimplementado en aquellas entidades que se pueden autodestruirm cada hija pone el tiempo a esperar antes de que se autodestruya, junto con la llamada a Destruir()*/

	this->SetActorLocation(FVector(0,0,-99999)); // Mover el actor para hacer pensar que se ha destruido (se destruirá después, para dar tiempo a audio a que se acabe de reproducir)

	
	
}




void AEntidad::BeginPlay() {
	Super::BeginPlay();

	this->ComponenteDeAudio->SetVolumeMultiplier(AEntidad::VolumenEfectos); // Settear el volumen de SFX en el componente de audio


	// Dar controller de IA

	AIControllerClass = AMandoDeIA::StaticClass();

	if (!this->Tags.Contains("NoIA")) {

		// Asignar IA ya que no contiene NoIA

		this->MandoDeIA = GetWorld()->SpawnActor<AMandoDeIA>();
		if (this->GetActorRotation().Yaw >= -85.f) {
			// Si está faceando al lado correcto al spawnear, darle la IA que le corresponde
			this->MandoDeIA->SettearIA(this->ID, Cast<ATorre>(this) != nullptr); // Decirle que clase es para settear el Behavior Tree adecuado

		} else {

			// Si esta rotado 270 grados de lo normal, es un robot en la pantalla de preview y requiere cargar una IA distinta
			this->MandoDeIA->SettearIA(255, Cast<ATorre>(this) != nullptr); // Decirle que clase es para settear el Behavior Tree adecuado

		}

		this->MandoDeIA->Possess(this);

	} else {

		// Si no tienen IA, no deberían contabilizar vida. Entidades sin IA se usan como decoración

		this->SetVulnerable(false);
	}




}


void AEntidad::SetVulnerable(bool Vulnerable) {

	UComponenteVida* ComponenteVida = FindComponentByClass<UComponenteVida>();

	if (ComponenteVida) {
		ComponenteVida->SetVulnerable(Vulnerable);
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