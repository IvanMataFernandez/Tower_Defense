// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TorreUsoInst_Ejecutar.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Torre_UsoInstantaneo.h"
#include "AIController.h"

UBTTask_TorreUsoInst_Ejecutar::UBTTask_TorreUsoInst_Ejecutar() {
      NodeName = "TorreInst_Ejecutar";

}

 EBTNodeResult::Type UBTTask_TorreUsoInst_Ejecutar::ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) {

    Super::ExecuteTask(BT,NodeMemory);
    Cast<ATorre_UsoInstantaneo>(BT.GetAIOwner()->GetPawn())->InicializacionFuncion();
    return EBTNodeResult::InProgress;

 }
