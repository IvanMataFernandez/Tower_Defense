// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Robot.h"
#include "Robot_Basico.generated.h"
/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API ARobot_Basico : public ARobot
{
	GENERATED_BODY()
	
public:

	ARobot_Basico();

	virtual void BeginPlay() override;


// Atributos

private:


	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float TiempoPorDisparo;

	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float TiempoParaAnimacionDisparo;

	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float RangoEnCasillas;


	
	


	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SpawnProyectiles;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshDisparador;


	UPROPERTY(EditDefaultsOnly, Category = "ClasesNecesarias")
	TSubclassOf<AProyectil> ClaseBlueprintProyectil;

// Métodos


public:
	void InicializarAtaque();
	bool TorreEnRango();

private:

	void Atacar(float DeltaTime);
	void RepetirAtaque();
	void Disparar();

};
