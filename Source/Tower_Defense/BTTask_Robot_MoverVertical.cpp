// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Robot_MoverVertical.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Robot.h"
#include "AIController.h"

UBTTask_Robot_MoverVertical::UBTTask_Robot_MoverVertical() {
      NodeName = "Robot_MoverVertical";

}

 EBTNodeResult::Type UBTTask_Robot_MoverVertical::ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) {

    Super::ExecuteTask(BT,NodeMemory);
    Cast<ARobot>(BT.GetAIOwner()->GetPawn())->InicializarMoverVertical(this->FrameRate);
    return EBTNodeResult::InProgress;


 }
