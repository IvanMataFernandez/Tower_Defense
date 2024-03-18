// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Casilla.generated.h"

UCLASS()
class TOWER_DEFENSE_API ACasilla : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACasilla();



// Métodos

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



// Atributos

private:

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite, meta= (AllowPrivateAccess = "true"))
	AActor* Torre; 


// Métodos:


public:
	UFUNCTION(BlueprintImplementableEvent)
	void SpawnearTorre(uint8 ID);
	void LiberarCasilla();
	bool CasillaVacia();


	bool ColocarTorre(int IDTorre); 



};
