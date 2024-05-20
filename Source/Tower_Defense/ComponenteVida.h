// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ComponenteVida.generated.h"
class GameMode_EnPartida;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWER_DEFENSE_API UComponenteVida : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComponenteVida();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


// Atrubutos

private:

	UPROPERTY(EditAnywhere, Category = "Datos")
	float VidaMaxima;
	float Vida;
	bool Vulnerable;



// Métodos
public:
	UFUNCTION()
	virtual void AplicarDano(AActor* Danado, float DanoBase, const UDamageType* TipoDano, AController* Instigator, AActor* Causador);

protected:
	float ObtenerFraccionVidaRestante();

public:
	bool EsVulnerable();
	void Invulnerabilizar();
	void Vulnerabilizar();

};
