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

 	bool TieneIA();
	void ActivarIA(bool Activar);

	void AcabarTareaActual();
	
	void SettearBoolEnBlackboard(FName Key, bool Valor);
//	bool GetBoolDeBlackboard(FName Key);

};
