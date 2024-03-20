// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TorreProd_Producir.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Torre_Producidor.h"
#include "AIController.h"

UBTTask_TorreProd_Producir::UBTTask_TorreProd_Producir() {
      NodeName = "TorreProd_Producir";

}

 EBTNodeResult::Type UBTTask_TorreProd_Producir::ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) {

    Super::ExecuteTask(BT,NodeMemory);
    Cast<ATorre_Producidor>(BT.GetAIOwner()->GetPawn())->PrepararTorre();
    return EBTNodeResult::InProgress;

 }
