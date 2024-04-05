// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Entidad_QuitarIA.generated.h"

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API UBTTask_Entidad_QuitarIA : public UBTTaskNode
{
	GENERATED_BODY()

public:	
	UBTTask_Entidad_QuitarIA();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) override;
};
