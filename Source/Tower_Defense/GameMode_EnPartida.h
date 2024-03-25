// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_EnPartida.generated.h"
class AZonaSpawnRobot;
class AMusica_EnPartida;
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

	int PesoRobotsVivo;
	int PesoTargetParaSiguienteOleada;

	bool SeAproximaOrdaGrande;
	bool SeQuiereSpawnearLaSiguienteOleada;

	AZonaSpawnRobot* ZonaSpawn;
	AMusica_EnPartida* ReproductorEnPartida;

	TArray<TSharedPtr<FJsonValue>> OleadasJson;
	FTimerHandle TimerParaSpawnRobot;
	FTimerHandle TimerParaOleadas;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TArray<int> GrandesOleadas;

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

public:

	void ProcesarMuerteDeRobot(int PesoDeRobot);

	UFUNCTION(BlueprintImplementableEvent)
	void ComunicarOleadasUI();
	
	UFUNCTION(BlueprintImplementableEvent)
	void ComunicarAvanceOleadaUI();	


private:

	void CargarNivel(int Nivel);
	void EmpezarJuego();
	TArray<int> EncontrarGrandesOleadas();
	void EmpezarCargaDeSiguienteOleada();
	void CargarDatosOleada();
	void GenerarOleada();
	void GenerarOleadaGrande();

	void GenerarRobot();
	void SpawnearRobot(int ID);





	
};
