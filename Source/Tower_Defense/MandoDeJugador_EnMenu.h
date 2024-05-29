// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MandoDeJugador_EnMenu.generated.h"
class UUserWidget;

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API AMandoDeJugador_EnMenu : public APlayerController
{
	GENERATED_BODY()
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



// Atributos

private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> ClaseHUDMenuPrincipal;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> ClaseHUDMenuTutorial;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> ClaseHUDMenuAjustes;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> ClaseHUDPopUpJuegoCompleto;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> ClaseHUDAvisoJuegoNuevo;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> ClaseHUDCarga;

	UUserWidget* HUD;

// Metodos

public:

	UFUNCTION(BlueprintCallable)
	UUserWidget* CambiarAInterfaz(int ID);


};
