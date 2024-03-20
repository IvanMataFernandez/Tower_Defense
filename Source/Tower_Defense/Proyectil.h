// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Proyectil.generated.h"
class UStaticMeshComponent;

UCLASS()
class TOWER_DEFENSE_API AProyectil : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProyectil();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


// Atributos

private:
	

	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	bool ProyectilDeTorre;

	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float VelocidadDeCaida;


	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	int CapacidadDestruccion; // Daño, compilador no acepta ñ
	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float Velocidad; // En eje Y.  Torres usan +, Robots usan -
	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	int ObjetivosMaximos;

	int ObjetivosRestantes;

	float Sentido;

	FTimerHandle TimerParaAutodestruir;

	

// Métodos

private:
	UFUNCTION()
	void EnColision(UPrimitiveComponent* ComponenteNuestro, AActor* OtroActro, UPrimitiveComponent* OtroComponente, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Resultado);

	void Caducar();

};
