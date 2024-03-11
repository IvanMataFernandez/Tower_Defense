// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TorreDisp_InicializarAtaq.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Torre_Disparador.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"




// TODO: More Tasks

UBTTask_TorreDisp_InicializarAtaq::UBTTask_TorreDisp_InicializarAtaq() {
    NodeName = "TorreDisp_InicializarAtaque";
}


 EBTNodeResult::Type UBTTask_TorreDisp_InicializarAtaq::ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) {

    Super::ExecuteTask(BT,NodeMemory);
    ATorre_Disparador* Pawn = Cast<ATorre_Disparador>(BT.GetAIOwner()->GetPawn());
    Pawn->InicializacionAtaque();
    

    return EBTNodeResult::Succeeded;





 }
