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

	/*
		Una save en este juego incluye:

			- El nivel en el que estás
			- Si ha superado el último nivel (necesario para guiar interfaces)
			- Si se ha completado el juego al menos una vez
			- La lista de torres desbloqueadas (sus IDs)
			- Los settings de volumen de música y sfx que el objeto settings de Unreal Engine no incluye

		Al reiniciar una save de cero, se restablecen todos los campos menos los settings de volumen, que siempre persisten.
	
	*/

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
