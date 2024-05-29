// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ZonaMenuSpawnProyectiles.generated.h"

UCLASS()
class TOWER_DEFENSE_API AZonaMenuSpawnProyectiles : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZonaMenuSpawnProyectiles();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


// Atributos:

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UBoxComponent* ZonaDeSpawn;

private:
	float SizeX;
	float SizeZ;
	FTimerHandle Timer;

	UPROPERTY(EditAnywhere)
	float FrecuenciaSpawnPorSegundo;

// Funciones:


protected:
	UFUNCTION(BlueprintImplementableEvent)
	void SpawnProyectil(float posX, float posZ);
	void ProgramarSpawn();

	UFUNCTION(BlueprintCallable)
	void DetenerSpawns();

};
