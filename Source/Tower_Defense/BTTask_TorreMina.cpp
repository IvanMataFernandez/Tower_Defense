// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TorreMina.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Torre_Disparador.h"
#include "Torre_Mina.h"
#include "AIController.h"


/*
    Instrucciones posibles:
        0: Preparandose 
        1: Preparado para poder detonar cuando un robot la pise
        (el estado de detonar es el uso unico de TorreUsoUnico)


*/


UBTTask_TorreMina::UBTTask_TorreMina() {
      NodeName = "TorreMina";

}

 EBTNodeResult::Type UBTTask_TorreMina::ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) {

      Super::ExecuteTask(BT,NodeMemory);
      ATorre_Mina* Torre = Cast<ATorre_Mina>(BT.GetAIOwner()->GetPawn());

      switch (this->IdInstruccion) {

      case 0:
            Torre->Prepararse();
            return EBTNodeResult::InProgress;

      case 1:
            Torre->Preparado();
            return EBTNodeResult::InProgress;

      }
      return EBTNodeResult::Failed;


 }
