// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_EnPartida.generated.h"
class AZonaSpawnRobot;
class AMusica_EnPartida;
class AZonaSpawnRobotPreview;
class APlayerPawn_EnPartida;


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

	APlayerPawn_EnPartida* Camara;

	AZonaSpawnRobot* ZonaSpawn;
	AZonaSpawnRobotPreview* ZonaSpawnPreview;
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

	void SpawnearRobotsPreview();

	void ProcesarMuerteDeRobot(int PesoDeRobot);

	UFUNCTION(BlueprintCallable)
	TArray<int> ObtenerCostesDeTorres(TArray<int> IDs);
	UFUNCTION(BlueprintCallable)
	TArray<float> ObtenerRecargasDeTorres(TArray<int> IDs);
	UFUNCTION(BlueprintCallable)
	TArray<bool> ObtenerEmpiezaRecargadosTorres(TArray<int> IDs);

	UFUNCTION(BlueprintCallable)
	TArray<UTexture2D*> ObtenerImagenesDeTorres(TArray<int> IDs);



protected:

	UFUNCTION(BlueprintCallable)
	void FinSeleccionTorres(TArray<int> IDsTorresElegidas);

	UFUNCTION(BlueprintImplementableEvent)
	void CrearInterfazSeleccionDeTorres();

	UFUNCTION(BlueprintImplementableEvent)
	void CrearInterfazDePartida();
	
	UFUNCTION(BlueprintImplementableEvent)
	void ComunicarAvanceOleadaUI();	

private:


	void CargarNivel(int Nivel);

	void EliminarRobotsPreview();

	void EmpezarJuego();

	TArray<int> EncontrarGrandesOleadas();
	void EmpezarCargaDeSiguienteOleada();
	void CargarDatosOleada();
	void GenerarOleada();
	void GenerarOleadaGrande();

	void GenerarRobot();
	void SpawnearRobot(int ID);

public:

	void EmpezarSeleccionDeTorres();
	void CargarCuentaAtrasParaEmpezarJuego();




	
};
