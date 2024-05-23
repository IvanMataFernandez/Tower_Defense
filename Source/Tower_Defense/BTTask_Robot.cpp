// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Robot.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Robot.h"
#include "AIController.h"

/*
    Instrucciones posibles:
        0: Empezar a mover horizontalmente 
        1: Empezar a mover verticalmente
        2: Parar


*/

UBTTask_Robot::UBTTask_Robot() {
      NodeName = "RobotBasico";

}

 EBTNodeResult::Type UBTTask_Robot::ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) {

      Super::ExecuteTask(BT,NodeMemory);
      ARobot* Robot = Cast<ARobot>(BT.GetAIOwner()->GetPawn());


      switch (this->IdInstruccion) {
            case 0: 
                  Robot->InicializarMover();
                  return EBTNodeResult::InProgress;

            case 1:
                  Robot->InicializarMoverVertical();
                  return EBTNodeResult::InProgress;
            case 2:
                  Robot->Parar();
                  return EBTNodeResult::Succeeded;
      }

      return EBTNodeResult::Failed;


 }