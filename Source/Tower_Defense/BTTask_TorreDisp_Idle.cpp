// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TorreDisp_Idle.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Torre_Disparador.h"
#include "AIController.h"


UBTTask_TorreDisp_Idle::UBTTask_TorreDisp_Idle() {
      NodeName = "TorreDisp_Idle";

}

 EBTNodeResult::Type UBTTask_TorreDisp_Idle::ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) {

    Super::ExecuteTask(BT,NodeMemory);
    Cast<ATorre_Disparador>(BT.GetAIOwner()->GetPawn())->PrepararIdle();
    return EBTNodeResult::InProgress;


 }
