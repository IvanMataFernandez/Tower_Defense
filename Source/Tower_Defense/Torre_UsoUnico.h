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





// Atributos


protected:
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* ZonaDeAfecto;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float DanoDeExplosion;



	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float TiempoParaExplosion;
	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float TiempoDeExplosion;



// Métodos

public:

	void InicializacionFuncion();


protected:


	virtual void AutoDestruir() override;

private:

	void Activar();
	void HacerFuncion();


	
};
