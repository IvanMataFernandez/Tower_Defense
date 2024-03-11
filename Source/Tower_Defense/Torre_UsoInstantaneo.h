// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Torre.h"
#include "Torre_UsoInstantaneo.generated.h"
class UBoxComponent;

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API ATorre_UsoInstantaneo : public ATorre
{
	GENERATED_BODY()


public:
	ATorre_UsoInstantaneo();


protected:

	virtual void BeginPlay() override;



// Atributos

private:

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* ZonaDeAfecto;
	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float TiempoParaAnimacion;


// Métodos

public:

	void HacerFuncion(float DeltaTime);

private:

	void Activar();


	
};
