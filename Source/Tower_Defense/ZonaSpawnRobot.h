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



	UPROPERTY(BlueprintReadOnly)
	TArray<float> PosicionesDeSpawn;


// Métodos

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SpawnearRobot(int ID ,int Fila); 

};
