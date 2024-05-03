// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entidad.h"
#include "Torre.generated.h"

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API ATorre : public AEntidad
{
	GENERATED_BODY()



// Métodos

public:

	virtual void Matar() override;




};
