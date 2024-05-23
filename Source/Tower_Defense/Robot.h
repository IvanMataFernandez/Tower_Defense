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

private:
//  UPROPERTY()
	float VelocidadActual;
	float Velocidad;

	float DistanciaRecorridaVertical;
	int Oleada;


	UPROPERTY(EditAnywhere, Category = "Datos", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float VelocidadBase;

	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float DesviacionMaxVelocidad;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshDesplazador;



// Métodos




public:


	virtual void Matar() override;
	virtual void QuitarIA() override;


	virtual void InicializarMoverVertical();
	virtual void InicializarMover();

	void SetOleada(int Oleada);
	int GetOleada();


	void MoverVertical(float DeltaTime);
	bool HaMovidoEnVerticalDistanciaX(float Distancia);
	void Mover(float DeltaTime);
	void SetVelocidad(float Vel);
	void Parar();





};
