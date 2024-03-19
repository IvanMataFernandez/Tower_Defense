// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZonaTargetRobot.generated.h"
class UBoxComponent;

UCLASS()
class TOWER_DEFENSE_API AZonaTargetRobot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZonaTargetRobot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



// Atributos

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UBoxComponent* ZonaTarget;


// Métodos

public:
	UFUNCTION()
	void EnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
