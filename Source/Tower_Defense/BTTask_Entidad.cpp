// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Entidad.h"
#include "Entidad.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "AIController.h"


/*
    Instrucciones posibles:
        - Quitar IA


*/

UBTTask_Entidad::UBTTask_Entidad() {
      NodeName = "Entidad_QuitarIA";

}

 EBTNodeResult::Type UBTTask_Entidad::ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) {

    Super::ExecuteTask(BT,NodeMemory);
    Cast<AEntidad>(BT.GetAIOwner()->GetPawn())->QuitarIA();
    return EBTNodeResult::InProgress;


 }
