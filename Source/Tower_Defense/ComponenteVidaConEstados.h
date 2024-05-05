// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ComponenteVida.h"
#include "ComponenteVidaConEstados.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWER_DEFENSE_API UComponenteVidaConEstados : public UComponenteVida
{
	GENERATED_BODY()


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


// Atrubutos

private:

UPROPERTY(EditAnywhere, Category = "Datos")
	int NumEstados;

	int Estado;  


// Métodos

public:
	virtual void AplicarDano(AActor* Danado, float DanoBase, const UDamageType* TipoDano, AController* Instigator, AActor* Causador) override;




};
