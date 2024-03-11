// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Torre.h"
#include "Torre_Producidor.generated.h"
class UStaticMeshComponent;

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API ATorre_Producidor : public ATorre
{
	GENERATED_BODY()


public:
	ATorre_Producidor();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


// Atributos

private:


	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Placas;
	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float TiempoParaAnimacion;

	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float CantidadProducida;


// Métodos

private:
	void Producir();

public:
	void Idle(float DeltaTime);

};

