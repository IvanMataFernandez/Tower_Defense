// Fill out your copyright notice in the Description page of Project Settings.


#include "ZonaSpawnRobot.h"
#include "Components/BoxComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Robot.h"


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
	FVector TamañoDeArea = this->ZonaDeSpawn->GetScaledBoxExtent();
	float LongX = TamañoDeArea.X;


	for (int i = 0; i != 5; i++) {
		PosicionesDeSpawn.Add(LongX * (0.4 * i - 0.8));
	}


    this->TamanoBox = this->ZonaDeSpawn->GetScaledBoxExtent();
	this->Localizacion = AActor::GetActorLocation();   

	for (int Fila = 0; Fila != 5; Fila++) {
		this->EspacioOcupadoPorFila.Add(FMath::FRand() * 300.f);
	}


}

ARobot* AZonaSpawnRobot::SpawnearRobot(int ID ,int Fila) {

	// Crea un robot del id adecuado en la fila indicada y devuelve el puntero a dicho robot creado. Cada vez que se spawnea un bot en la misma fila, se le pone algo más
	// atrás para que no overlapee con el de adelante. Además, se da un poco de aleatoriedad a los espacios entre robots.
	
	FVector Pos = FVector(this->Localizacion.X + this->PosicionesDeSpawn[Fila], this->Localizacion.Y + this->EspacioOcupadoPorFila[Fila] , this->Localizacion.Z - this->TamanoBox.Z );
	ARobot* Robot = this->MaterealizarRobot(ID, Pos);
	
	this->EspacioOcupadoPorFila[Fila] = this->EspacioOcupadoPorFila[Fila] + 260.f + FMath::FRand() * 300.f;

	return Robot;
}


void AZonaSpawnRobot::RefrescarNuevaOleada() {

	// Resettear los spawns para decirle a la zona que vuelva a empezar a spawnear bots desde el punto más cercano adelante posible.

	for (int Fila = 0; Fila != this->EspacioOcupadoPorFila.Num(); Fila++) {
		this->EspacioOcupadoPorFila[Fila] = FMath::FRand() * 300.f;

	}

}


ARobot* AZonaSpawnRobot::MaterealizarRobot_Implementation(int ID, FVector Posicion) {
	// NOP. Está en blueprint. Genera el robot en sí físicamente según el ID de instancia robot blueprint dada y su posicion en el nivel
	return nullptr;
}


