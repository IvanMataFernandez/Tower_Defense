// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MandoDeJugador_EnPartida.generated.h"
class UUserWidget;
class UTexture2D;

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API AMandoDeJugador_EnPartida : public APlayerController
{
	GENERATED_BODY()





protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

//public:	
	// Called every frame
//	virtual void Tick(float DeltaTime) override;



// Atributos

private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> ClaseHUDElegirTorre;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> ClaseHUDCuentaAtras;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> ClaseHUDEnPartida;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> ClaseHUDDerrota;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> ClaseHUDVictoria;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> ClaseHUDPausa;

	TArray<UUserWidget*> HUDs;




	TArray<int> IDsDeTorresElegidas;
	TArray<float> TiempoDeRecargaDeTorres;
	TArray<int> CosteDeTorres;
	TArray<float> MomentoEnQueTorreRecarga;
	int SeleccionDelJugador; // 0-5 torres, 6 TNT, -1 nothing

	int Energia;

	bool EnPartida; // True si en partida, False si en seleccion de torres

public:


// Métodos


	void PausarEn(float Segundos);

	
	void SetTorresElegidas(TArray<int> IDs);


	UFUNCTION(BlueprintCallable)
	TArray<int> GetTorresElegidas() const;


	void InicializarVariablesDePartida();
		
	void Pinchar();

	UFUNCTION(BlueprintCallable)
	UUserWidget* CrearHUD(int Seleccion);


	UFUNCTION(BlueprintCallable)
	UUserWidget* ObtenerHUD(int Pos) const;



	UFUNCTION(BlueprintCallable)
	void QuitarUltimaHUDAnadida();

	UFUNCTION(BlueprintCallable)
	void QuitarHUD(int Pos);









	UFUNCTION(BlueprintCallable)
	TArray<int> ObtenerCostesDeTorres(TArray<int> IDs);
	UFUNCTION(BlueprintCallable)
	TArray<float> ObtenerRecargasDeTorres(TArray<int> IDs);
	UFUNCTION(BlueprintCallable)
	TArray<bool> ObtenerEmpiezaRecargadosTorres(TArray<int> IDs);

	UFUNCTION(BlueprintCallable)
	TArray<UTexture2D*> ObtenerImagenesDeTorres(TArray<int> IDs);


	UFUNCTION(BlueprintCallable)
	void ElegirTorre(int PosTorre, bool& SeleccionCorrecta, int& SeleccionPrevia, bool& SeleccionPreviaCorrecta);

	UFUNCTION(BlueprintCallable)
	void ElegirTNT(int& SeleccionPrevia, bool& TntElegida);

	UFUNCTION(BlueprintCallable)
	void ObtenerUltimaSeleccionTorre(int& Seleccion, bool& Correcto) const;

	bool TNTElegida();


	void ActualizarEnergiaPor(int Surplus);
	void UsarSeleccionElegida();


	UFUNCTION(BlueprintCallable)
	int ObtenerCantidadEnergia() const;

	UFUNCTION(BlueprintImplementableEvent)
	void NotificarAInterfazColoqueTorre(int Pos);

	UFUNCTION(BlueprintImplementableEvent)
	void NotificarAInterfazUsoTNT();


	UFUNCTION(BlueprintImplementableEvent)
	void NotificarAInterfazCambioEnDinero(int Cantidad);



private:


	int ObtenerIDDeTorreElegida();


	void Pausar();




};
