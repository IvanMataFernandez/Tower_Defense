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
	UPROPERTY()
	float Velocidad;




private:

	float DistanciaRecorridaVertical;

	UPROPERTY(EditAnywhere, Category = "Datos", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float VelocidadBase;

	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float DesviacionMaxVelocidad;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshDesplazador;



// Métodos


public:
	virtual void InicializarMoverVertical();
	void MoverVertical(float DeltaTime);
	bool HaMovidoEnVerticalDistanciaX(float Distancia);

	virtual void InicializarMover();
	void Mover(float DeltaTime);



	virtual void Matar() override;
	virtual void QuitarIA() override;

};
