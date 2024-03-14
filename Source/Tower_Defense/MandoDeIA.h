// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MandoDeIA.generated.h"

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API AMandoDeIA : public AAIController
{
	GENERATED_BODY()



// Atributos:



// Métodos
public:
	void SettearIA(uint8 Clase);

	virtual void BeginPlay() override;

	
};
