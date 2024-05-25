// Fill out your copyright notice in the Description page of Project Settings.


#include "Proyectil.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Entidad.h"




// Esta clase hereda a todo proyectil del juego


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


	// Cuando aparece un proyectil, vincular la acción de colisión con el método EnColision()

	this->Mesh->OnComponentBeginOverlap.AddDynamic(this, &AProyectil::EnColision);

	// Inicializar el contador de objetivos máximos dañables

	this->ObjetivosRestantes = this->ObjetivosMaximos;

	// Dependiendo de la clase blueprint instanciada, la ha disparado una torre o una entidad. Su variable booleana respectiva indica quien disparo
	// y por lo tanto, el sentido en el que viaja la bala (torres disparan hacia la derecha, robots hacia la izquierda)

	if (this->ProyectilDeTorre) {
		this->Sentido = 1.f;
	} else {
		this->Sentido = -1.f;

	}
	
	// Fallsave, si de alguna forma el proyectil no colisiona y destruye, se autodestruye a los 25s
    GetWorld()->GetTimerManager().SetTimer(this->TimerParaAutodestruir, this, &AProyectil::Caducar, 25.f, false);               

}

void AProyectil::SetVelocidadDeCaida(float DistVert, float DistHor) {

	// Settear la velocidad de caída del proyectil (usado solo por robots, settean su velocidad de caída tan pronto como instancian la bala)

	// La velocidad de caida se settea en proporción a la distancia vertical que se debe hacer respecto a la horizontal

	this->VelocidadDeCaida = (DistVert/DistHor) * this->Velocidad;

	AActor::SetActorRotation(FRotator(0,0,-45*(this->VelocidadDeCaida/this->Velocidad))); // Rotar la bala para que parezca que tiene gravedad aplicandola

}


void AProyectil::Pausar() {
	this->Velocidad = 0.f;
	this->VelocidadDeCaida = 0.f;
	GetWorld()->GetTimerManager().ClearTimer(this->TimerParaAutodestruir);
	PrimaryActorTick.bCanEverTick = false;

}


void AProyectil::Caducar() {
	Destroy();
}


// Called every frame
void AProyectil::Tick(float DeltaTime)
{


	Super::Tick(DeltaTime);
	
	// Mover el proyectil en la dirección Y. Si tiene velocidad de caida, aplicar una caída también

	FVector Loc = AActor::GetActorLocation();
	Loc.Y = Loc.Y + this->Sentido * DeltaTime * this->Velocidad;
	Loc.Z = Loc.Z - this->VelocidadDeCaida * DeltaTime;
	AActor::SetActorLocation(Loc);


}

void AProyectil::EnColision(UPrimitiveComponent* ComponenteNuestro, AActor* OtroActor, UPrimitiveComponent* OtroComponente, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Resultado) {


	// Si una bala colisiona con algo, llega la ejecución aquí


	if (Cast<AEntidad>(OtroActor)) {

		// Si choca con una entidad, aplicar el daño (las balas solo activan colisiones contra entidades del bando contrario a la que la hizo aparecer)

		UGameplayStatics::ApplyDamage(OtroActor, this->CapacidadDestruccion, nullptr, this, UDamageType::StaticClass());
		this->AnimarHit(); // Animar por blueprint el hit (poniendo efectos especiales)
		this->ObjetivosRestantes--; // Restar uno al contador de objetivos restantes que puede perforar
	} else {
		// Si se colisionó con algo que no es una entidad, eliminar inmediatamente el proyectil, para ello, poner su capacidad de perforación restante a 0
		this->ObjetivosRestantes = 0;

	}
	


	// Si ya ha gastado todos sus targets, eliminarla

	if (this->ObjetivosRestantes == 0) {
		GetWorld()->GetTimerManager().ClearTimer(this->TimerParaAutodestruir); // Quitar la programación de la fallsave de quitar el proyectil a los 25s

		Destroy(); // Quitarlo ahora en su lugar
	}
}

