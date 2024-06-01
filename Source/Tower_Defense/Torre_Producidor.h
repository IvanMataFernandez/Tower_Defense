// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Torre.h"
#include "Torre_Producidor.generated.h"
class UStaticMeshComponent;
class AMandoDeJugador_EnPartida;

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API ATorre_Producidor : public ATorre
{
	GENERATED_BODY()


public:
	ATorre_Producidor();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



// Componentes:

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Placas;


// Atributos

private:

	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	int CantidadProducida;


	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float TiempoProduccionBase;
	
	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float DesviacionTiempoProduccionMax;

	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float TiempoHastaQueCaducaEnergia;

	bool EnergiaDisponible;
	bool PrimeraProduccion;

	AMandoDeJugador_EnPartida* MandoDeJugador;

// Métodos


public:
	void PrepararParaProduccion();
	void Click();
	void Producir();
	void FinProduccion(); 


};

