// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Casilla.generated.h"

class ATorre;
class UAudioComponent;

UCLASS()
class TOWER_DEFENSE_API ACasilla : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACasilla();





// Atributos

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta= (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	ATorre* Torre; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,  meta= (AllowPrivateAccess = "true"))
	UAudioComponent* ComponenteDeAudio;


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
