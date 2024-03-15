// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entidad.h"
#include "Robot.generated.h"
class USceneComponent;
class UStaticMeshComponent;
class AProyectil;
/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API ARobot : public AEntidad
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARobot();

	virtual void BeginPlay() override;


// Atributos

protected:

	float Velocidad;

private:

	UPROPERTY(EditAnywhere, Category = "Datos")
	float VelocidadBase;

	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float DesviacionMaxVelocidad;




	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshDesplazador;



// Métodos


public:
	void InicializarMover(float FrameRate);
	void Mover(float DeltaTime);



};
