// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Robot_Basico.h"
#include "Robot_Bomba.generated.h"
class UBoxComponent;

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API ARobot_Bomba : public ARobot_Basico
{
	GENERATED_BODY()
	
public:

	ARobot_Bomba();



// Atributos

protected:
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* AreaDeExplosion;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float DanoDeExplosion;


	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float TiempoParaExplosion;

	
	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float TiempoDeExplosion;




// Métodos

public:

	virtual void Matar() override; 
	virtual void ProcesarFinDeVida() override;


protected:

	virtual void AutoDestruir() override;

private:
	void EmpezarDetonar();

	void Detonar();






};
