// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TorreUsoUnico_Ejecutar.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Torre_UsoUnico.h"
#include "AIController.h"

UBTTask_TorreUsoUnico_Ejecutar::UBTTask_TorreUsoUnico_Ejecutar() {
      NodeName = "TorreUsoUnic_Ejecutar";

}

 EBTNodeResult::Type UBTTask_TorreUsoUnico_Ejecutar::ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) {

    Super::ExecuteTask(BT,NodeMemory);
    Cast<ATorre_UsoUnico>(BT.GetAIOwner()->GetPawn())->InicializacionFuncion();
    return EBTNodeResult::InProgress;

 }
