// Fill out your copyright notice in the Description page of Project Settings.


#include "ZonaSpawnRobot.h"
#include "Components/BoxComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Robot.h"




// Sets default values
AZonaSpawnRobot::AZonaSpawnRobot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	this->ZonaDeSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("Zona de Spawn"));
	RootComponent = this->ZonaDeSpawn;

}

// Called when the game starts or when spawned
void AZonaSpawnRobot::BeginPlay()
{
	Super::BeginPlay();
	FVector TamañoDeArea = this->ZonaDeSpawn->GetScaledBoxExtent();
	float LongX = TamañoDeArea.X;


	for (int i = 0; i != 5; i++) {
		PosicionesDeSpawn.Add(LongX * (0.4 * i - 0.8));
	}

    this->TamanoBox = this->ZonaDeSpawn->GetScaledBoxExtent();
	this->Localizacion = AActor::GetActorLocation();   

	for (int Fila = 0; Fila != 5; Fila++) {
		this->EspacioOcupadoPorFila.Add(FMath::FRand() * 150.f);
	}


}

ARobot* AZonaSpawnRobot::SpawnearRobot(int ID ,int Fila) {

	// Crea un robot del id adecuado en la fila indicada y devuelve el puntero a dicho robot creado
	
	FVector Pos = FVector(this->Localizacion.X + this->PosicionesDeSpawn[Fila], this->Localizacion.Y + this->EspacioOcupadoPorFila[Fila] , this->Localizacion.Z - this->TamanoBox.Z );
	ARobot* Robot = this->MaterealizarRobot(ID, Pos);
	
	this->EspacioOcupadoPorFila[Fila] = this->EspacioOcupadoPorFila[Fila] + 320.f + FMath::FRand() * 150.f;

	return Robot;
}


void AZonaSpawnRobot::RefrescarNuevaOleada() {

	for (int Fila = 0; Fila != this->EspacioOcupadoPorFila.Num(); Fila++) {
		this->EspacioOcupadoPorFila[Fila] = FMath::FRand() * 150.f;

	}

}


ARobot* AZonaSpawnRobot::MaterealizarRobot_Implementation(int ID, FVector Posicion) {
	return nullptr;
}


