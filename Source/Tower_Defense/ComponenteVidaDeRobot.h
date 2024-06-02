#pragma once

#include "CoreMinimal.h"
#include "ComponenteVidaConEstados.h"
#include "ComponenteVidaDeRobot.generated.h"
class ARobot;
/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWER_DEFENSE_API UComponenteVidaDeRobot : public UComponenteVidaConEstados
{
	GENERATED_BODY()
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

// Atributos:

private:
	ARobot* Robot;

// Métodos

public:
	virtual void AplicarDano(AActor* Danado, float DanoBase, const UDamageType* TipoDano, AController* Instigator, AActor* Causador) override;



};
