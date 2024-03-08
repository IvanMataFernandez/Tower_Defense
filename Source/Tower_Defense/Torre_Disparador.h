// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Torre.h"
#include "Torre_Disparador.generated.h"
class USceneComponent;
class AProyectil;

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API ATorre_Disparador : public ATorre
{


	GENERATED_BODY()

public:	
	ATorre_Disparador();
	void BeginPlay();


// Atributos

private:
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SpawnProyectiles;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProyectil> ClaseBlueprintProyectil;


	UPROPERTY(EditDefaultsOnly)
	int CadenciaDeDisparo;
	UPROPERTY(EditDefaultsOnly)
	float CooldownInicial;
	UPROPERTY(EditDefaultsOnly)
	float TiempoEntreTiros;
	int TirosRestantes;
	float SigTiroEn;
// Métodos

public:
	void PrepararIdle();
	void Idle();
	void EnRango();
	void InicializacionAtaque();
	void Atacar(float DeltaTime);

private:
	void Disparar();

};
