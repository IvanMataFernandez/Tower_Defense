// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Guardador.generated.h"

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API UGuardador : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	int Nivel;
	UPROPERTY(BlueprintReadWrite)
	bool UltimoNivelSuperado;
	UPROPERTY(BlueprintReadWrite)
	bool JuegoCompleto;
	UPROPERTY(BlueprintReadWrite)
	TArray<int> IDsTorresDesbloqueadas;
	UPROPERTY(BlueprintReadWrite)
	float VolumenAudio;
	UPROPERTY(BlueprintReadWrite)
	float VolumenSFX;
};
