// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Robot_Bomba.h"
#include "Robot_BombaRadar.generated.h"

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API ARobot_BombaRadar : public ARobot_Bomba
{
	GENERATED_BODY()
	




// Atributos:

private:

	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	int CantTorresParaDetonar;


// Metodos

public:

	bool SuficientesTorresEnRangoDeExplosion();



};
