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

	UPROPERTY(EditDefaultsOnly, Category = "ClasesNecesarias")
	TSubclassOf<AProyectil> ClaseBlueprintProyectil;

	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	int RangoEnCasillas;
	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	int CadenciaDeDisparo;
	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float CooldownFinal;
	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float TiempoEntreTiros;
	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float TiempoParaAnimacionEnTiro;
	int TirosRestantes;
	float SigTiroEn;

	bool TocaAnimar;


// Métodos

public:
	void PrepararIdle();
	bool EnRango();
	void InicializacionAtaque();


private:
	void Disparar();
	void Atacar(float DeltaTime);



};
