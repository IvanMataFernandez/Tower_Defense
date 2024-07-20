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



// Una entidad es todo Robot o Torre. Una entidad no se instancia por ella misma.


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
	// Programa un timer usando el Delegate dado  (incluye el método y sus parametros), así como el tiempo de espera para ejecutarlo y si debe
	// ser ejecutado en bucle.

	// Cada entidad solo tiene un timer simultaneo, y cancela el anterior si un nuevo timer es programado sobre ella

	// Los timers sirven para bufferear instrucciones como acabar de ejecutar una tarea de su BT, o esperar a procesar el cálculo del daño de una detonación

    GetWorld()->GetTimerManager().SetTimer(TimerFrame, Delegate, TiempoDeEspera, EnBucle);
}


void AEntidad::ProgramarTimerFinDeTareaIA(float TiempoEspera) {

	// La tarea de programar el fin de una tarea de su BT es tan común que existe este método para ahorrar pasaos en la llamada al método de arriba.
	// Si el tiempo de espera es menor a 0.01s, entonces se ejecuta directamente la finalización de la tarea de su BT en vez de encolarlo con su timer.

	if (TiempoEspera > 0.01f) {
		FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this->MandoDeIA, &AMandoDeIA::AcabarTareaActual);    
		this->ProgramarTimer(Delegate, TiempoEspera, false);
	
	} else {
		this->MandoDeIA->AcabarTareaActual();
	}
	

}


uint8 AEntidad::ObtenerID() {
	return this->ID; // Cada tipo de instancia de entidad en blueprint (torre y robot), tiene un ID propio.
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

	// Settear Trace Responses de Visto por Robot y Torre a ignore, para que las entidades no puedan targettearlo. Esto no impide que no pueda absorber proyectiles

	this->Hitbox->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel5, ECollisionResponse::ECR_Ignore);
	this->Hitbox->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel6, ECollisionResponse::ECR_Ignore);

}


void AEntidad::DesactivarHitbox() {

 	// Quitar hitbox para que los enemigos ignoren a esta entidad (no la puedan ver) y los proyectiles la sobrepasen. 

	this->Hitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}


void AEntidad::ProcesarFinDeVida() {

	/*
		Cuando una entidad debe ser eliminada (expceto si es una torre que se quita con TNT), sigue el siguiente recorrido para eliminar los datos
		correspondientes en el siguiente orden:

		ProcesarFinDeVida() [clase hija] -> ProcesarFinDeVida() [clase padre] -> Matar() [clase hija] -> Matar() [clase padre]
	
	
	*/

	// Tras acabar de procesar los pasos iniciales de que una entidad debe morir, pasar a los pasos de eliminarla del nivel.
	// La clase entidad no requiere realizar pasos adiciones aquí
	this->Matar();
	
	
	}


void AEntidad::Matar() {
	// Se llama a este método cuando vida = 0. Es la última llamada de la cadena del procesamiento de la eliminación de una entidad


	this->QuitarIA(); // Desactivar la IA si no se había hecho ya antes
	this->DesactivarHitbox(); // Quitar la hitbox de la entidad


	// Comprobar si la entidad tenia componente de vida y es vulnerable, si lo es, entonces animar su muerte
	// Si no cumple la condicion, la unidad se habria automatado y no tiene sentido animar esa muerte (ej, matarse tras haber realizado una explosion)

	UComponenteVida* ComponenteVida = FindComponentByClass<UComponenteVida>();

	if (ComponenteVida && ComponenteVida->EsVulnerable()) {
		this->RealizarAnimacion(0); // realizar animación de muerte (por blueprints)
		GetWorld()->GetTimerManager().SetTimer(TimerFrame, this, &AEntidad::Destruir,this->TiempoDeAnimacionDeMuerte, false); // Esperar para que la animación acabe para quitar la entidad del nivel

	} else {
		this->AutoDestruir(); // Sirve para ocultar temporalmente la entidad fuera de la pantalla (para que suenen sus SFXs) hasta que se elimine
		                      // definitivamente
	}
}

void AEntidad::QuitarIA() {

	// Elimina la IA de la entidad

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
	}

	// Detener animaciones

	this->DestruirAnimaciones();
	
	// Parar timer global de la clase
	this->ClearTimer();

}


void AEntidad::DespausarEntidad() {


	// Despausar IA

	AMandoDeIA* IA = Cast<AMandoDeIA>(this->GetController());

	IA->ActivarIA(true);
	

	// La IA activa las animaciones de nuevo

}

void AEntidad::Destruir() {
	AActor::Destroy(); // Eliminar la entidad (Robot o Torre, debe eliminarse igual)
}

void AEntidad::AutoDestruir() {
	

	/* Reimplementado en aquellas entidades que se pueden autodestruir cada hija pone el tiempo a esperar antes de que se autodestruya, junto con la llamada a Destruir()*/

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
			// Si está faceando hacia la derecha al spawnear, darle la IA que le corresponde al robot
			this->MandoDeIA->SettearIA(this->ID, Cast<ATorre>(this) != nullptr); // Decirle que clase blueprint es (ID) para settear el Behavior Tree adecuado

		} else {

			// Si mirando hacia abajo, es un robot en la pantalla de preview y requiere cargar una IA distinta
			this->MandoDeIA->SettearIA(255, Cast<ATorre>(this) != nullptr); // El ID 255 carga la IA especial de moverse hacia abajo en vez de lado.

		}

		this->MandoDeIA->Possess(this);

	} else {

		// Si no tienen IA, no deberían contabilizar vida. Entidades sin IA se usan como decoración (en el menú principal)

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

	// Cancelar el timer activo (si hay) de la entidad
    GetWorld()->GetTimerManager().ClearTimer(this->TimerFrame);
            

}


AMandoDeIA* AEntidad::GetMandoDeIA() {
	return this->MandoDeIA;
}

FVector AEntidad::ObtenerRadioHitbox() {
	return this->Hitbox->GetScaledBoxExtent();
}