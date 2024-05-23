// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Entidad.generated.h"

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API UBTTask_Entidad : public UBTTaskNode
{
	GENERATED_BODY()

public:	
	UBTTask_Entidad();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) override;
};
