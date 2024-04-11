// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Torre_UsoUnico.h"
#include "Torre_Mina.generated.h"
class ZonaTrigger;

UCLASS()
class TOWER_DEFENSE_API ATorre_Mina : public ATorre_UsoUnico
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATorre_Mina();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;





// Atributos

private:

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* ZonaTrigger;

	UPROPERTY(EditDefaultsOnly, Category = "datos")
	float TiempoDePreparacion;

// Métodos:

public: 

	void Prepararse();
	void Preparado();


private:
	UFUNCTION()
	void EnContacto(UPrimitiveComponent* ComponenteNuestro, AActor* OtroActor, UPrimitiveComponent* OtroComponente, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Resultado);


};
