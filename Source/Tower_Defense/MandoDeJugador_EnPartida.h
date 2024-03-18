// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MandoDeJugador_EnPartida.generated.h"
class UUserWidget;

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
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true") )
	UUserWidget* HUD;




// Métodos

public:

	UPROPERTY(BlueprintReadWrite)
	int SeleccionDeTorre;

	void Pinchar();

	UFUNCTION(BlueprintImplementableEvent)
	void SettearSeleccionDeTorre();


};
