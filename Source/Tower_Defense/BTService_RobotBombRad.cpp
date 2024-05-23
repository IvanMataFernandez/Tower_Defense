// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_RobotBombRad.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Robot_BombaRadar.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


/*
    Instrucciones posibles:
        - Mirar si hay X torres en radio de explosion


*/


void UBTService_RobotBombRad::TickNode(UBehaviorTreeComponent &BT, uint8 *NodeMemory, float DeltaTime) {
    Super::TickNode(BT, NodeMemory, DeltaTime);
    BT.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(),  Cast<ARobot_BombaRadar>(BT.GetAIOwner()->GetPawn())->SuficientesTorresEnRangoDeExplosion());
   
}
