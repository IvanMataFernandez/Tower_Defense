// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TorreUsoUnico_Ejecutar.generated.h"

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API UBTTask_TorreUsoUnico_Ejecutar : public UBTTaskNode
{
	GENERATED_BODY()

public:	
	UBTTask_TorreUsoUnico_Ejecutar();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) override;



};
