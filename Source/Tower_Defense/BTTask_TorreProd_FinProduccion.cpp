// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TorreProd_FinProduccion.h"
#include "Torre_Producidor.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "AIController.h"


UBTTask_TorreProd_FinProduccion::UBTTask_TorreProd_FinProduccion() {
      NodeName = "Productor_FinDeProduccion";

}

 EBTNodeResult::Type UBTTask_TorreProd_FinProduccion::ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) {

    Super::ExecuteTask(BT,NodeMemory);
    Cast<ATorre_Producidor>(BT.GetAIOwner()->GetPawn())->FinProduccion();
    return EBTNodeResult::Succeeded;


 }

