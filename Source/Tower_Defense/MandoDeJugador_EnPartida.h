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




	TArray<int> IDsTorresDesbloqueadas;

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

	
	UFUNCTION(BlueprintCallable)
	void ProcesarClickEnSeleccionInicialDeTorres(int Slot, bool& AccionValida, bool& Eliminacion, int& CantidadSelecciones, TArray<int>& SlotsARetroceder, bool& PermiteEmpezar);



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
	float ObtenerRecargaDeTorre(int ID) const;
	UFUNCTION(BlueprintCallable)
	bool ObtenerEmpiezaRecargadoTorre(int ID) const;

	UFUNCTION(BlueprintCallable)	
	int ObtenerCosteDeTorre(int ID) const;
	
	UFUNCTION(BlueprintCallable)
	UTexture2D* ObtenerImagenDeTorre(int ID) const;


	UFUNCTION(BlueprintCallable)
	void ObtenerTodasLasImagenesYCostesDeTorre(TArray<UTexture2D*>& Imagenes, TArray<int>& Costes) const;

	UFUNCTION(BlueprintCallable)
	void ElegirTorre(int PosTorre, bool& Encender, bool& Correcto, int& SeleccionPrevia);

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

	int SlotDeTorreDesbloqueadaEnPosDeSeleccion(int Slot);

	int IDDeTorreASlotDeSave(int ID);


	int ObtenerIDDeTorreElegidaEnPartida();


	void Pausar();




};
