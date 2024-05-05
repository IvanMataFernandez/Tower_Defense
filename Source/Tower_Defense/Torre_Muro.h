// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Torre.h"
#include "Torre_Muro.generated.h"

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API ATorre_Muro : public ATorre
{
	GENERATED_BODY()
	

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
// Métodos
	virtual void Matar() override;

};
