// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_RobotBombRad_VerTorres.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Robot_BombaRadar.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_RobotBombRad_VerTorres::TickNode(UBehaviorTreeComponent &BT, uint8 *NodeMemory, float DeltaTime) {
    Super::TickNode(BT, NodeMemory, DeltaTime);
    BT.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(),  Cast<ARobot_BombaRadar>(BT.GetAIOwner()->GetPawn())->SuficientesTorresEnRangoDeExplosion());
   
}
