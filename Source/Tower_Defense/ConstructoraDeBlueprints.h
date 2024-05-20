// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
class UBehaviorTree;
class ATorre;
class UUserWidget;
/**
 * 
 */

UENUM(BlueprintType)
enum class Torres :uint8 {


	// 0x00 - 0x07 -> Disparadores
	Canon = 0x00,
	CanonDoble = 0x01,
	PistolaLaser = 0x02,

	// 0x08 - 0x0A -> Producidores
	PanelSolar = 0x08,
	PanelSolarDoble = 0x09,

	// 0x0B - 0x0F -> Usos Unicos
	Mina = 0x0B,
	Bomba = 0x0C,

	// 0x10 - 0x13 -> Muros

	Escudo = 0x10


};

UENUM(BlueprintType)
enum class Robots :uint8 {

	// 0x00 - 0x07 -> Básicos
	Basico = 0x00,
	LiderOleada = 0x01,
	Medio = 0x02,
	Duro = 0x03,

	// 0x08 - 0x10 -> Especiales

	Bomba = 0x08,
	BombaRadar = 0x09,
	Ocultador = 0x0A,

	// 0xFF -> IA reservada para preview, usable por todo bot
	Preview = 0xFF



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
//	UClass* ClaseBomba;

public:
	static ConstructoraDeBlueprints* GetConstructoraDeBlueprints();
	UBehaviorTree* GetBT(uint8 Clase, bool Torre);


	float GetTiempoDeRecargaDeTorre(uint8 Clase);
	bool GetEmpiezaRecargadaTorre(uint8 Clase);

	int GetCosteDeTorre(uint8 Clase);

	int GetPesoDeRobot(uint8 Clase);

	TArray<UTexture2D*> ObtenerImagenesDeTorres(TArray<int> IDs);

	TArray<int> ObtenerCostesDeTorres(TArray<int> IDs);

};
