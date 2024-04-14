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
	TSubclassOf<class UUserWidget> ClaseHUDMenuAjustes;

	UUserWidget* HUD;

// Metodos

public:

	UFUNCTION(BlueprintCallable)
	void CambiarAInterfaz(int ID);


};
