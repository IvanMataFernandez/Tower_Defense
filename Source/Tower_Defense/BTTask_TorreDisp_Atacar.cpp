// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TorreDisp_Atacar.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Torre_Disparador.h"
#include "AIController.h"


UBTTask_TorreDisp_Atacar::UBTTask_TorreDisp_Atacar() {
      NodeName = "TorreDisp_InicializarAtacar";

}

 EBTNodeResult::Type UBTTask_TorreDisp_Atacar::ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) {

    Super::ExecuteTask(BT,NodeMemory);
    ATorre_Disparador* Torre = Cast<ATorre_Disparador>(BT.GetAIOwner()->GetPawn());
    Torre->InicializacionAtaque();
    return EBTNodeResult::InProgress;


 }









    



