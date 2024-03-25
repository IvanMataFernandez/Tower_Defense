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
	TSubclassOf<class UUserWidget> ClaseHUD;
	
	UUserWidget* HUD;





public:


	UPROPERTY(BlueprintReadWrite)
	int SeleccionDeTorre;

// Métodos


	void Pinchar();

	UFUNCTION(BlueprintCallable)
	UUserWidget* ObtenerHUD() const;

	UFUNCTION(BlueprintImplementableEvent)
	void SettearSeleccionDeTorre();

	UFUNCTION(BlueprintImplementableEvent)
	void SettearBorradorDeTorre();

	UFUNCTION(BlueprintCallable)
	TArray<int> ObtenerCostesDeTorres(TArray<int> IDs);
	UFUNCTION(BlueprintCallable)
	TArray<float> ObtenerRecargasDeTorres(TArray<int> IDs);
	UFUNCTION(BlueprintCallable)
	TArray<bool> ObtenerEmpiezaRecargadosTorres(TArray<int> IDs);

	UFUNCTION(BlueprintCallable)
	TArray<UTexture2D*> ObtenerImagenesDeTorres(TArray<int> IDs);

	UFUNCTION(BlueprintImplementableEvent)
	void IncrementarEnergia(int Cantidad);



};
