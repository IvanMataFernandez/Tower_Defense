// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_RobotBombRad_VerTorres.generated.h"

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API UBTService_RobotBombRad_VerTorres : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	

	
protected:
	virtual void TickNode(UBehaviorTreeComponent &BT, uint8 *NodeMemory, float DeltaTime) override;	

};
