// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_EnPartida.generated.h"
class AZonaSpawnRobot;

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API AGameMode_EnPartida : public AGameModeBase
{
	GENERATED_BODY()


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;




// Atributos


private:

	AZonaSpawnRobot* ZonaSpawn;

	TArray<TSharedPtr<FJsonValue>> OleadasJson;
	FTimerHandle TimerParaSpawnRobot;
	FTimerHandle TimerParaOleadas;

	int OleadaActual;
	int OleadasTotales;
	float HastaSiguienteOleada;

	TArray<int> IDsRobot;
	TArray<int> PesosRobot;
	TArray<float> ProbabilidadesRobotAcumuladas;

	int PesoRestante;
	float TiempoEntreSpawn;


	TArray<int> PesosRobotActual;
	TArray<int> IDsRobotActual;

	

// Métodos

private:

	void CargarNivel(int Nivel);
	void EmpezarCargaDeSiguienteOleada();
	void CargarDatosOleada();
	void SpawnearRobot();





	
};
