// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Torre.h"
#include "Torre_Disparador.generated.h"
class USceneComponent;
class AProyectil;

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API ATorre_Disparador : public ATorre
{


	GENERATED_BODY()

public:	
	ATorre_Disparador();
	void BeginPlay();



// Componentes

protected:


	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SpawnProyectiles;

// Atributos
private:

	UPROPERTY(EditDefaultsOnly, Category = "ClasesNecesarias")
	TSubclassOf<AProyectil> ClaseBlueprintProyectil;

	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	int RangoEnCasillas;
	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	int CadenciaDeDisparo;
	
	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float TiempoDeCiclo;

	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float TiempoParaApuntar;

	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float TiempoAnimarDisparo;

	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float TiempoDisparo;





// Métodos

public:

	int ObtenerCadenciaDeDisparo();

	bool EnRango();

	void Apuntar();
	void AnimarDisparo(int DisparosRestantes);
	void Disparar();
	void EsperaFinDeCicloDeAtaque();

	void PrepararDesapuntar();

private:
	void Desapuntar();


};
