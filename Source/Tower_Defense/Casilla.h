// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Casilla.generated.h"

class ATorre;
class UAudioComponent;
class UBoxComponent;

UCLASS()
class TOWER_DEFENSE_API ACasilla : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACasilla();




// Componentes

protected:

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* CampoAntiRobot; // Solo permite colocar torre aquí si no hay robots pisando esta zona, excepto para instant kills

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta= (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,  meta= (AllowPrivateAccess = "true"))
	UAudioComponent* ComponenteDeAudio;


// Atributos

private:



	ATorre* Torre; 

	static float VolumenEfectos;




// Métodos:


public:
	UFUNCTION(BlueprintImplementableEvent)
	void SpawnearTorre(uint8 ID);
	void QuitarReferenciaTorre();
	void DestruirTorre();

	bool CasillaVacia();
	ATorre* ObtenerTorreEnCasilla();

	UFUNCTION(BlueprintCallable)
	static void SetVolumenEfectosDeCasillas(float Vol, UObject* ContextoMundo);


	bool RobotPisandoFinalDeCasilla();


protected:
	UFUNCTION(BlueprintImplementableEvent)
	void PonerMaterialBase();
	
	UFUNCTION(BlueprintCallable)
	void PonerTorre(ATorre* NuevaTorre);

	UFUNCTION(BlueprintImplementableEvent)
	void AnimarPonerTorre();
	
	UFUNCTION(BlueprintImplementableEvent)
	void AnimarDestruirTorre();

};
