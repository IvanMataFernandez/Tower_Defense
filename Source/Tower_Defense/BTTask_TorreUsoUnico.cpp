// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TorreUsoUnico.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Torre_UsoUnico.h"
#include "AIController.h"

/*
    Instrucciones posibles:
        - Ejecutar accion de uso unico


*/

UBTTask_TorreUsoUnico::UBTTask_TorreUsoUnico() {
      NodeName = "TorreUsoUnic_Ejecutar";

}

 EBTNodeResult::Type UBTTask_TorreUsoUnico::ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) {

    Super::ExecuteTask(BT,NodeMemory);
    Cast<ATorre_UsoUnico>(BT.GetAIOwner()->GetPawn())->InicializacionFuncion();
    return EBTNodeResult::InProgress;

 }
