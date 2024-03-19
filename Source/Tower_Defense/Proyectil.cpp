// Fill out your copyright notice in the Description page of Project Settings.


#include "Proyectil.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Entidad.h"

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
	
	// Fallsave, si de alguna forma el proyectil no colisiona, se autodestruye a los 25s
    GetWorld()->GetTimerManager().SetTimer(this->TimerParaAutodestruir, this, &AProyectil::Caducar, 25.f, false);               
 	AActor::SetActorRotation(FRotator(0,0,-45*(this->VelocidadDeCaida/this->Velocidad)));

}
void AProyectil::Caducar() {
	Destroy();
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




	if (Cast<AEntidad>(OtroActor)) {
		UGameplayStatics::ApplyDamage(OtroActor, this->CapacidadDestruccion, nullptr, this, UDamageType::StaticClass());
		this->ObjetivosRestantes--;
	} else {
		// Si se colisionó con algo que no es una entidad, eliminar inmediatamente el proyectil
		this->ObjetivosRestantes = 0;

	}
	


	// Si ya ha gastado todos sus targets, eliminar

	if (this->ObjetivosRestantes == 0) {
		GetWorld()->GetTimerManager().ClearTimer(this->TimerParaAutodestruir);

		Destroy();
	}
}

