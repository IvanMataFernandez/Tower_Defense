// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Robot_Matarse.h"
#include "Robot.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "AIController.h"


UBTTask_Robot_Matarse::UBTTask_Robot_Matarse() {
      NodeName = "Robot_Matarse";

}

 EBTNodeResult::Type UBTTask_Robot_Matarse::ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) {

    Super::ExecuteTask(BT,NodeMemory);
    Cast<ARobot>(BT.GetAIOwner()->GetPawn())->Matar();
    return EBTNodeResult::InProgress;


 }