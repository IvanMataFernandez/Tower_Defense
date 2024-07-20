// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RobotBombRad.h"
#include "Robot_BombaRadar.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "AIController.h"


/*
    Instrucciones posibles:
        - Detonación prematura


*/

UBTTask_RobotBombRad::UBTTask_RobotBombRad() {
      NodeName = "Robot_Matarse";

}

 EBTNodeResult::Type UBTTask_RobotBombRad::ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) {

    Super::ExecuteTask(BT,NodeMemory);
    Cast<ARobot_BombaRadar>(BT.GetAIOwner()->GetPawn())->ForzarExplosion();
    return EBTNodeResult::InProgress;


 }