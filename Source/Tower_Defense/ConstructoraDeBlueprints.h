// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
class UBehaviorTree;
class ATorre;
/**
 * 
 */

UENUM(BlueprintType)
enum class Rutas :uint8 {

	// 0x00 - 0xFF -> Torres

		// 0x00 - 0x07 -> Disparadores
	Canon = 0x00,
	CanonDoble = 0x01,
	PistolaLaser = 0x02,

		// 0x08 - 0x0A -> Producidores
	PanelSolar = 0x08,
	PanelSolarDoble = 0x09,

		// 0x0B - W/E -> Usos instantaneos
	Bomba = 0x0B


};


class TOWER_DEFENSE_API ConstructoraDeBlueprints
{
private:
	ConstructoraDeBlueprints();

public:
	~ConstructoraDeBlueprints();

// Atributos

private:
	static ConstructoraDeBlueprints Objeto;
	UClass* ClaseBomba;

public:
	static ConstructoraDeBlueprints* GetConstructoraDeBlueprints();
	UBehaviorTree* GetBT(uint8 Clase);

};
