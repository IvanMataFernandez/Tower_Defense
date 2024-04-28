// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Casilla.generated.h"

class ATorre;

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

	UPROPERTY(BlueprintReadWrite, meta= (AllowPrivateAccess = "true"))
	ATorre* Torre; 


// Métodos:


public:
	UFUNCTION(BlueprintImplementableEvent)
	void SpawnearTorre(uint8 ID);
	void QuitarTorre();
	void LiberarCasilla();
	bool CasillaVacia();
	ATorre* ObtenerTorreEnCasilla();






};
