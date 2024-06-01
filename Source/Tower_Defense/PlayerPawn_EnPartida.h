// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn_EnPartida.generated.h"

class UCameraComponent;

UCLASS()
class TOWER_DEFENSE_API APlayerPawn_EnPartida : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn_EnPartida();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


// Atributos

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCameraComponent* Camara;

private:

	FTimerHandle Timer;
	FTimerHandle TimerRotacion;

	float VelX;
	float VelY;
	float VelZ;
	float TiempoAct;
	float TiempoTotal;
	FVector PosTarget;

	float VelPitch;
	float TiempoActRot;
	float TiempoTotalRot;
	FRotator RotTarget;


	float DeltaTiempo;



// Métodos


public:
	void MoverCamASeleccion();
	void MoverCamAJugar();
	void MoverCamAIzquierda();

private:

	void Pinchar();
	void MoverCamA(float X, float Y, float Z, float Duracion);
	void RotarCamEnPitchA(float Pitch, float Duracion);
	void MoverCam();
	void RotarCam();



};
