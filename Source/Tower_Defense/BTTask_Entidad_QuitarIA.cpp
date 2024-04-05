// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Entidad_QuitarIA.h"
#include "Entidad.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "AIController.h"


UBTTask_Entidad_QuitarIA::UBTTask_Entidad_QuitarIA() {
      NodeName = "Entidad_QuitarIA";

}

 EBTNodeResult::Type UBTTask_Entidad_QuitarIA::ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) {

    Super::ExecuteTask(BT,NodeMemory);
    Cast<AEntidad>(BT.GetAIOwner()->GetPawn())->QuitarIA();
    return EBTNodeResult::InProgress;


 }
