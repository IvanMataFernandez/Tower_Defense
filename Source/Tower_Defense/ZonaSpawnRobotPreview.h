
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZonaSpawnRobotPreview.generated.h"
class UBoxComponent;

UCLASS()
class TOWER_DEFENSE_API AZonaSpawnRobotPreview : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AZonaSpawnRobotPreview();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;




// Atributos



protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UBoxComponent* ZonaDeSpawn;

private:
	int ContadorSpawns;

	


// Métodos

public:

	void SpawnearRobot(int ID);

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void EventoSpawnearRobot(int ID ,int Numero); 

};


