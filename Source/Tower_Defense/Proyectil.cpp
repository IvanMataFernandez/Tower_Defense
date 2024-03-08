// Fill out your copyright notice in the Description page of Project Settings.


#include "Proyectil.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AProyectil::AProyectil()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void AProyectil::BeginPlay()
{
	Super::BeginPlay();
	this->Mesh->OnComponentBeginOverlap.AddDynamic(this, &AProyectil::EnColision);

	
}

// Called every frame
void AProyectil::Tick(float DeltaTime)
{


	Super::Tick(DeltaTime);
	
	// Mover el proyectil en la dirección Y.

	FVector Loc = AActor::GetActorLocation();
	Loc.Y = Loc.Y + DeltaTime * this->Velocidad;
	AActor::SetActorLocation(Loc);


}

void AProyectil::EnColision(UPrimitiveComponent* ComponenteNuestro, AActor* OtroActor, UPrimitiveComponent* OtroComponente, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Resultado) {


	// TODO: Crear 4 canales de colision. (Proyectil Torre, Proyectil Robot, Torre, Robot), settear cada uno al tipo de colision adecuado y handlear colisiones

	// Handlear daño aquí


	// Handlear penetración aquí. Restar uno a penetración si enemy. Settear penetración a cero si hitbox de las esquinas del nivel



	// Si ya ha gastado todos sus targets, eliminar

	if (this->ObjetivosRestantes == 0) {
		Destroy();
	}
}
