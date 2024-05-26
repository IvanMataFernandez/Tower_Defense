// Fill out your copyright notice in the Description page of Project Settings.


#include "ZonaSpawnRobot.h"
#include "Components/BoxComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Robot.h"
#include "Kismet/GameplayStatics.h"


// La zona invisible que hace aparecer los robots de la partida que vienen desde la derecha


AZonaSpawnRobot::AZonaSpawnRobot()
{
	PrimaryActorTick.bCanEverTick = false;
	this->ZonaDeSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("Zona de Spawn"));
	RootComponent = this->ZonaDeSpawn;

}

// Called when the game starts or when spawned
void AZonaSpawnRobot::BeginPlay()
{

	// Calcular los 5 puntos donde pueden aparecer los robots (uno por cada fila)

	Super::BeginPlay();
	this->Radio = this->ZonaDeSpawn->GetScaledBoxExtent();
	float RadioX = this->Radio.X;
	this->TamanoCasillaX = RadioX / 2.5f;

	for (int i = 0; i != 5; i++) {
		PosicionesDeSpawn.Add(RadioX * (0.4 * i - 0.8));
	}


	this->Localizacion = AActor::GetActorLocation();   

	for (int Fila = 0; Fila != 5; Fila++) {
		this->EspacioOcupadoPorFila.Add(100 + FMath::FRand() * 200.f);
	}


}

ARobot* AZonaSpawnRobot::SpawnearRobot(int ID ,int Fila) {

	// Crea un robot del id adecuado en la fila indicada y devuelve el puntero a dicho robot creado. Cada vez que se spawnea un bot en la misma fila, se le pone algo más
	// atrás para que no overlapee con el de adelante. Además, se da un poco de aleatoriedad a los espacios entre robots.
	


	FVector Pos = FVector(this->Localizacion.X + this->PosicionesDeSpawn[Fila], this->Localizacion.Y - this->Radio.Y  + this->EspacioOcupadoPorFila[Fila] , this->Localizacion.Z - this->Radio.Z );
	ARobot* Robot = this->MaterealizarRobot(ID, Pos);
	
	this->EspacioOcupadoPorFila[Fila] = this->EspacioOcupadoPorFila[Fila] + 260.f + FMath::FRand() * 300.f;

	return Robot;
}


void AZonaSpawnRobot::RefrescarNuevaOleada() {


	// Checkear si hay bots por detrás de la zona de spawns, para spawnear los nuevos bots aun más atrás

	TArray<float> AtrasoExtra;

	for (int i = 0; i != 5; i++) {
		AtrasoExtra.Add(0.f);
	}


	TArray<AActor*> Robots;

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARobot::StaticClass(), Robots);

    for (AActor* Entidad : Robots) {

		ARobot* Robot = Cast<ARobot>(Entidad);
		
		FVector PosRobot = Robot->GetActorLocation();

		int Fila = FMath::Floor(((PosRobot.X - this->Localizacion.X + this->Radio.X) / this->TamanoCasillaX));
		float DistanciaFondo = (PosRobot.Y - (this->Localizacion.Y - this->Radio.Y)) + Robot->ObtenerRadioHitbox().Y;




		if (DistanciaFondo > AtrasoExtra[Fila]) {
			AtrasoExtra[Fila] = DistanciaFondo;
		}
	}

	// Resettear los spawns para decirle a la zona que vuelva a empezar a spawnear bots desde el punto más cercano posible (en la zona de spawn o si hay bots ocupandola ya, detrás de ellos)

	for (int Fila = 0; Fila != this->EspacioOcupadoPorFila.Num(); Fila++) {
		this->EspacioOcupadoPorFila[Fila] = 100 + FMath::FRand() * 200.f + AtrasoExtra[Fila];
	}


}






ARobot* AZonaSpawnRobot::MaterealizarRobot_Implementation(int ID, FVector Posicion) {
	// NOP. Está en blueprint. Genera el robot en sí físicamente según el ID de instancia robot blueprint dada y su posicion en el nivel
	return nullptr;
}


