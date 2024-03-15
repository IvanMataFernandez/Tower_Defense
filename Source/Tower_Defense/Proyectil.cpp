// Fill out your copyright notice in the Description page of Project Settings.


#include "Proyectil.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProyectil::AProyectil()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = this->Mesh;
}

// Called when the game starts or when spawned
void AProyectil::BeginPlay()
{
	Super::BeginPlay();
	this->Mesh->OnComponentBeginOverlap.AddDynamic(this, &AProyectil::EnColision);

	this->ObjetivosRestantes = this->ObjetivosMaximos;

	if (this->ProyectilDeTorre) {
		this->Sentido = 1.f;
	} else {
		this->Sentido = -1.f;

	}
	

 	AActor::SetActorRotation(FRotator(0,0,-45*(this->VelocidadDeCaida/this->Velocidad)));

}

// Called every frame
void AProyectil::Tick(float DeltaTime)
{


	Super::Tick(DeltaTime);
	
	// Mover el proyectil en la dirección Y.

	FVector Loc = AActor::GetActorLocation();
	Loc.Y = Loc.Y + this->Sentido * DeltaTime * this->Velocidad;
	Loc.Z = Loc.Z - this->VelocidadDeCaida * DeltaTime;
	AActor::SetActorLocation(Loc);


}

void AProyectil::EnColision(UPrimitiveComponent* ComponenteNuestro, AActor* OtroActor, UPrimitiveComponent* OtroComponente, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Resultado) {



	// Handlear daño aquí


	// Handlear penetración aquí. Restar uno a penetración si enemy. Settear penetración a cero si hitbox de las esquinas del nivel


	
	UGameplayStatics::ApplyDamage(OtroActor, this->CapacidadDestruccion, nullptr, this, UDamageType::StaticClass());
	this->ObjetivosRestantes--;

	// Si ya ha gastado todos sus targets, eliminar

	if (this->ObjetivosRestantes == 0) {
		Destroy();
	}
}
