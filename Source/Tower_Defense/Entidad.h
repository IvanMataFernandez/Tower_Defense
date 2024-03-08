// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Entidad.generated.h"
class UBoxComponent;
class UStaticMeshComponent;
class USceneComponent;

UCLASS()
class TOWER_DEFENSE_API AEntidad : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEntidad();


// Atrubutos:

protected:

	float Timer;
	UPROPERTY(EditDefaultsOnly)
	float Ciclo;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* PosicionBase;
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* Hitbox;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* CuerpoBase;
//	UPROPERTY(EditDefaultsOnly)
//	UHealthComponent* Vida;

//	UPROPERTY(EditDefaultsOnly)
//  UAnimacionComponent Animador;

};
