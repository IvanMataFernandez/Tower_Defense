// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZonaSpawnRobot.generated.h"
class UBoxComponent;

UCLASS()
class TOWER_DEFENSE_API AZonaSpawnRobot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZonaSpawnRobot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;




// Atributos



protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UBoxComponent* ZonaDeSpawn;


private:

	TArray<float> PosicionesDeSpawn;
	TArray<float> EspacioOcupadoPorFila;

	FVector Localizacion;
	FVector TamanoBox;




// Métodos

public:

	UFUNCTION(BlueprintImplementableEvent)
	void MaterealizarRobot(int ID, FVector Posicion);

	void SpawnearRobot(int ID ,int Fila); 


	void RefrescarNuevaOleada();


};
