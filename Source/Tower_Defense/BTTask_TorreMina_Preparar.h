// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TorreMina_Preparar.generated.h"


UCLASS()
class TOWER_DEFENSE_API UBTTask_TorreMina_Preparar : public UBTTaskNode
{
	GENERATED_BODY()
	

public:	
	UBTTask_TorreMina_Preparar();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) override;





};
