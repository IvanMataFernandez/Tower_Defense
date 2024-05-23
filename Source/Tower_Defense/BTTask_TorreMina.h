// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TorreMina.generated.h"

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API UBTTask_TorreMina : public UBTTaskNode
{
	GENERATED_BODY()
	

public:	
	UBTTask_TorreMina();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) override;



private:

	UPROPERTY(EditAnywhere)
	int IdInstruccion;

};
