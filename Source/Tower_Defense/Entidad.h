// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Entidad.generated.h"
class UBoxComponent;
class UStaticMeshComponent;
class USceneComponent;
class UAudioComponent;

UCLASS()
class TOWER_DEFENSE_API AEntidad : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEntidad();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

// Atrubutos:



protected:
	// Referir a ConstructoraDeBlueprints para info de IDs.
	UPROPERTY(EditDefaultsOnly, Category = "ID")
	uint8 ID;

	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float TiempoDeAnimacionDeMuerte = 1.f;

	float Timer;

	FTimerHandle TimerFrame;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* PosicionBase;
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* Hitbox;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* CuerpoBase;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAudioComponent* ComponenteDeAudio;


//	UPROPERTY(EditDefaultsOnly)
//  UAnimacionComponent Animador;

// Métodos:

public:
	virtual void Matar();
	virtual void QuitarIA();
	void PausarEntidad();
    void DespausarEntidad();
	
	UFUNCTION(BlueprintImplementableEvent)
	void RealizarAnimacion(int Animacion);

protected:
	void ClearTimer();
	void Invisibilizar();
	void VisibilizarATorres();





	UFUNCTION(BlueprintImplementableEvent)
	void DestruirAnimaciones();

private:

	void Destruir();

};
