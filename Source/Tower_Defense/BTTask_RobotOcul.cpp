// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RobotOcul.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Robot_Ocultador.h"
#include "AIController.h"



/*
    Instrucciones posibles:
		- Ocultar
		- Desocultar

*/

UBTTask_RobotOcul::UBTTask_RobotOcul() {
      NodeName = "RobotOcul";

}

 EBTNodeResult::Type UBTTask_RobotOcul::ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) {

      Super::ExecuteTask(BT,NodeMemory);
      ARobot_Ocultador* Robot = Cast<ARobot_Ocultador>(BT.GetAIOwner()->GetPawn());

      switch (this->IdInstruccion) {

            case 0:
                  Robot->Ocultar();

                  return EBTNodeResult::Succeeded;


            case 1:
                  Robot->Desocultar();
                  return EBTNodeResult::InProgress;

      }

      return EBTNodeResult::Failed;


 }
