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
	float TiempoDeDisparo;

	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float TiempoDeAnimacionDisparo;

	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float RangoEnCasillas;


protected:
	
// Componentes

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SpawnProyectiles;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshDisparador;


	UPROPERTY(EditDefaultsOnly, Category = "ClasesNecesarias")
	TSubclassOf<AProyectil> ClaseBlueprintProyectil;

// Métodos


public:
	bool TorreEnRango();

	void AnimarDisparo();
	void Disparar();




};
