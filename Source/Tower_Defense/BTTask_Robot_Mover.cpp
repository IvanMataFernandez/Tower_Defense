// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Robot_Mover.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Robot.h"
#include "AIController.h"

UBTTask_Robot_Mover::UBTTask_Robot_Mover() {
      NodeName = "RobotBasico_Mover";

}

 EBTNodeResult::Type UBTTask_Robot_Mover::ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) {

    Super::ExecuteTask(BT,NodeMemory);
    Cast<ARobot>(BT.GetAIOwner()->GetPawn())->InicializarMover();
    return EBTNodeResult::InProgress;


 }