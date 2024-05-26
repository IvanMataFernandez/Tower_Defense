// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Robot_Basico.h"
#include "Robot_Ocultador.generated.h"
class UComponenteVida;
/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API ARobot_Ocultador : public ARobot_Basico
{
	GENERATED_BODY()
	

public:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:

	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float TiempoParaAbrirCerrarPuntoExpuesto;	



public:
	void Ocultar();
	void Desocultar();


//public:
//	virtual void InicializarMover() override;
//	virtual void InicializarAtaque() override;
//	virtual void InicializarMoverVertical() override;
//	virtual void QuitarIA() override;

//private:
//	void TrasCerrarPuntoExpuesto();
//	void TrasAbrirPuntoExpuesto();
	

};
