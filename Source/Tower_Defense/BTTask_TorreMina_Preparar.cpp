// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TorreMina_Preparar.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Torre_Disparador.h"
#include "Torre_Mina.h"
#include "AIController.h"


UBTTask_TorreMina_Preparar::UBTTask_TorreMina_Preparar() {
      NodeName = "TorreMina_Preparar";

}

 EBTNodeResult::Type UBTTask_TorreMina_Preparar::ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) {

    Super::ExecuteTask(BT,NodeMemory);
    Cast<ATorre_Mina>(BT.GetAIOwner()->GetPawn())->Prepararse();
    return EBTNodeResult::InProgress;


 }

