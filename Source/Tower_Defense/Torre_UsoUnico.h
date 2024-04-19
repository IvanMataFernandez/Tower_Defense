// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Torre.h"
#include "Torre_UsoUnico.generated.h"
class UBoxComponent;

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API ATorre_UsoUnico : public ATorre
{
	GENERATED_BODY()


public:
	ATorre_UsoUnico();


protected:

	virtual void BeginPlay() override;



// Atributos

private:

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* ZonaDeAfecto;

	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float DanoDeExplosion;



protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Datos")
	float TiempoParaExplosion;

// Métodos

public:

	void InicializacionFuncion();
private:

	void Activar();
	void HacerFuncion();


	
};
