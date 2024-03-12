// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_TorreDisp_BuscarRobot.generated.h"

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API UBTService_TorreDisp_BuscarRobot : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
protected:
	virtual void TickNode(UBehaviorTreeComponent &BT, uint8 *NodeMemory, float DeltaTime) override;
};
