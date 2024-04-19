// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Entidad_HacerAnimacion.h"
#include "Entidad.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "AIController.h"


UBTTask_Entidad_HacerAnimacion::UBTTask_Entidad_HacerAnimacion() {
      NodeName = "Entidad_HacerAnimacion";

}

 EBTNodeResult::Type UBTTask_Entidad_HacerAnimacion::ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) {

    Super::ExecuteTask(BT,NodeMemory);
    Cast<AEntidad>(BT.GetAIOwner()->GetPawn())->RealizarAnimacion(this->Animacion);
    return EBTNodeResult::Succeeded;


 }

