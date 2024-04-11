// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TorreMina_Preparado.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Torre_Disparador.h"
#include "Torre_Mina.h"
#include "AIController.h"


UBTTask_TorreMina_Preparado::UBTTask_TorreMina_Preparado() {
      NodeName = "TorreMina_Preparado";

}

 EBTNodeResult::Type UBTTask_TorreMina_Preparado::ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) {

    Super::ExecuteTask(BT,NodeMemory);
    Cast<ATorre_Mina>(BT.GetAIOwner()->GetPawn())->Preparado();
    return EBTNodeResult::InProgress;


 }
