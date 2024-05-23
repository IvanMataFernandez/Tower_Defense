// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RobotBas.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Robot_Basico.h"
#include "AIController.h"


/*
    Instrucciones posibles:
        - Animar Disparo
        - Disparar


*/

UBTTask_RobotBas::UBTTask_RobotBas() {
      NodeName = "RobotBasico";

}

 EBTNodeResult::Type UBTTask_RobotBas::ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) {

    Super::ExecuteTask(BT,NodeMemory);
    ARobot_Basico* Robot = Cast<ARobot_Basico>(BT.GetAIOwner()->GetPawn());


    switch (this->IdInstruccion) {
        case 0:
            Robot->AnimarDisparo();
            return EBTNodeResult::InProgress;

        case 1:
            Robot->Disparar();
            return EBTNodeResult::InProgress;

    }

    return EBTNodeResult::Failed;


 }