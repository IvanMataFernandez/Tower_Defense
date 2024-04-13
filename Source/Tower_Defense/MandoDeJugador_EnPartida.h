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

	TArray<int> IDTorresElegidas;


public:


	UPROPERTY(BlueprintReadWrite)
	int SeleccionDeTorre;

// Métodos

	void PausarEn(float Segundos);


	void SetTorresElegidas(TArray<int> IDs);


	UFUNCTION(BlueprintCallable)
	TArray<int> GetTorresElegidas() const;

	void Pinchar();

	UFUNCTION(BlueprintCallable)
	UUserWidget* CrearHUD(int Seleccion);


	UFUNCTION(BlueprintCallable)
	UUserWidget* ObtenerHUD(int Pos) const;



	UFUNCTION(BlueprintCallable)
	void QuitarUltimaHUDAnadida();

	UFUNCTION(BlueprintCallable)
	void QuitarHUD(int Pos);



	UFUNCTION(BlueprintImplementableEvent)
	void SettearSeleccionDeTorre();

	UFUNCTION(BlueprintImplementableEvent)
	void SettearBorradorDeTorre();

	UFUNCTION(BlueprintImplementableEvent)
	void IncrementarEnergia(int Cantidad);

private:

	void Pausar();




};
