// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sound/AmbientSound.h"
#include "Musica_EnPartida.generated.h"
class USoundBase;

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API AMusica_EnPartida : public AAmbientSound
{
	GENERATED_BODY()

public:


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

// Atributos
private:



	UPROPERTY(EditDefaultsOnly)
	USoundBase* MusicaInicio;
		
	UPROPERTY(EditDefaultsOnly)
	USoundBase* MusicaMedio;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* MusicaFin;
	
	UPROPERTY(EditDefaultsOnly)
	USoundBase* MusicaSeleccionDeTorres;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* MusicaCuentaAtras;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* MusicaRobotLlegaATarget;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* MusicaDerrota;

// Métodos

public:

	void Tocar(int ID);
	void Parar();
};
