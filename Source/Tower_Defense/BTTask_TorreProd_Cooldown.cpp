// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TorreProd_Cooldown.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Torre_Producidor.h"
#include "AIController.h"

UBTTask_TorreProd_Cooldown::UBTTask_TorreProd_Cooldown() {
      NodeName = "TorreProd_Cooldown";

}

 EBTNodeResult::Type UBTTask_TorreProd_Cooldown::ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) {

    Super::ExecuteTask(BT,NodeMemory);
    Cast<ATorre_Producidor>(BT.GetAIOwner()->GetPawn())->PrepararParaProduccion();
    return EBTNodeResult::InProgress;

 }
