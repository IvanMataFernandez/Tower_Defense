// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entidad.h"
#include "Robot.generated.h"
class USceneComponent;
class UStaticMeshComponent;
class AProyectil;
class UPrimitiveComponent;

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

	ARobot* LideradoPor;
	ARobot* LideraA;


	float VelocidadActual;
	float VelocidadDeInstancia;
	float VelocidadDeCola;

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

	virtual void ProcesarFinDeVida() override;

	virtual void QuitarIA() override;


	void InicializarMoverVertical();
	virtual void InicializarMover();
	virtual void Parar();

	void SetOleada(int Oleada);
	int GetOleada();




	void MoverVertical(float DeltaTime);
	bool HaMovidoEnVerticalDistanciaX(float Distancia);
	void Mover(float DeltaTime);
	void SetVelocidad(float Vel);


protected:

	virtual void Matar() override;

	ARobot* GetLideraA();
	bool EsLider();	
	
	virtual void DarInfoDeColaASubordinado(ARobot* Subordinado);


private:

    UFUNCTION()
    void EnChoque(UPrimitiveComponent* ComponenteNuestro, AActor* OtroActor, UPrimitiveComponent* OtroComponente, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Resultado
);

	void SetVelocidadDeCola(float Vel);

	void DeshacerEnlaceDeCola(bool Lider);


};
