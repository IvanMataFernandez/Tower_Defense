// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RobotBas_Atacar.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Robot_Basico.h"
#include "AIController.h"

UBTTask_RobotBas_Atacar::UBTTask_RobotBas_Atacar() {
      NodeName = "RobotBasico_Atacar";

}

 EBTNodeResult::Type UBTTask_RobotBas_Atacar::ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) {

    Super::ExecuteTask(BT,NodeMemory);
    Cast<ARobot_Basico>(BT.GetAIOwner()->GetPawn())->InicializarAtaque();
    return EBTNodeResult::InProgress;


 }