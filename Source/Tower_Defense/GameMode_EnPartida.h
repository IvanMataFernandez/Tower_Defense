// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_EnPartida.generated.h"
class AZonaSpawnRobot;
class AMusica_EnPartida;
class AZonaSpawnRobotPreview;
class APlayerPawn_EnPartida;
class ARobot;

UCLASS()
class TOWER_DEFENSE_API AGameMode_EnPartida : public AGameModeBase
{
	GENERATED_BODY()


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;




// Atributos


private:

	int NivelActual;

	int PesoRobotsVivo;
	int PesoPorEliminarHastaSiguienteOleada;

	bool SeAproximaOrdaGrande;
	bool SeQuiereSpawnearLaSiguienteOleada;

	APlayerPawn_EnPartida* Camara;

	AZonaSpawnRobot* ZonaSpawn;
	AZonaSpawnRobotPreview* ZonaSpawnPreview;

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
	


	TArray<int> PesosRobotActual;
	TArray<int> IDsRobotActual;

	TArray<int> FilasHabilitadasParaSpawn;

	bool VictoriaPosible;

	ARobot* CausanteDerrota;






// Métodos

public:

	void SpawnearRobotsPreview();

	void ProcesarMuerteDeRobot(int PesoDeRobot, ARobot* RobotMatado);

	void CongelarMundoPorDerrota(ARobot* Causante);
	void FocusearCausanteDerrota();
	void FinalizarAnimacionDerrota();






	void EmpezarSeleccionDeTorres();
	void CargarCuentaAtrasParaEmpezarJuego();


	UFUNCTION(BlueprintCallable)
	void EmpezarJuego();


	UFUNCTION(BlueprintCallable)
	void ProcesarClickEnRecompensa();

	UFUNCTION(BlueprintCallable)
	void AvanzarNivel(int TorreDesbloqueo);





// ---------------------------------------------------------





protected:

	UFUNCTION(BlueprintImplementableEvent)
	void TocarMusica(int Id);	


	UFUNCTION(BlueprintImplementableEvent)
	void SonarSFXGlobal();	

	UFUNCTION(BlueprintCallable)
	void FinSeleccionTorres();

	UFUNCTION(BlueprintImplementableEvent)
	void CrearInterfazSeleccionDeTorres();

	UFUNCTION(BlueprintImplementableEvent)
	void CrearInterfazDeCuentaAtras();

	UFUNCTION(BlueprintImplementableEvent)
	void CrearInterfazDePartida();


	UFUNCTION(BlueprintImplementableEvent)
	void CrearInterfazDeDerrota();

	UFUNCTION(BlueprintImplementableEvent)
	void QuitarInterfaz();
	
	UFUNCTION(BlueprintImplementableEvent)
	void ComunicarAvanceOleadaUI();	

	UFUNCTION(BlueprintImplementableEvent)
	void ComunicarAvisoDeOleadaGrande();	

	UFUNCTION(BlueprintImplementableEvent)
	void ComunicarVictoria(int Nivel, float PosXDrop, float PosYDrop);	

private:


	bool CargarNivel(int Nivel);
	int ConseguirDesbloqueo(int Nivel);

	void EliminarRobotsPreview();


	TArray<int> EncontrarGrandesOleadas();
	void EmpezarCargaDeSiguienteOleada();
	void EmpezarCargaDePrimeraOleada();

	void CargarDatosOleada();
	void GenerarOleada();
	void GenerarOleadaGrande();

	void GenerarRobot();
	void SpawnearRobot(int PosRobotEntreDisponibles);

	void JugadorGana(ARobot* UltimoRobotMatado);


	void ProcesarCorrupcionDeDatos();


	
};
