// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Torre.h"
#include "Torre_Producidor.generated.h"

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API ATorre_Producidor : public ATorre
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


// Atributos

private:

	UPROPERTY(EditDefaultsOnly)
	float TiempoParaAnimacion;


// Métodos

private:
	void Producir();

public:
	void Idle(float DeltaTime);

};

