// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MandoDeIA.generated.h"
class UBehaviorTree;
/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API AMandoDeIA : public AAIController
{
	GENERATED_BODY()



// Atributos:

private:

	UBehaviorTree* BT;

// Métodos
public:
	void SettearIA(uint8 Clase, bool Torre);


	void ActivarIA(bool Activar);

public:

	void AcabarTareaActual();

};
