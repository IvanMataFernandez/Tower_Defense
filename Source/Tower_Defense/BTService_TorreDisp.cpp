// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_TorreDisp.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Torre_Disparador.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


/*
    Instrucciones posibles:
        - Mirar si hay robot en rango


*/


void UBTService_TorreDisp::TickNode(UBehaviorTreeComponent &BT, uint8 *NodeMemory, float DeltaTime) {
    Super::TickNode(BT, NodeMemory, DeltaTime);
    BT.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(),  Cast<ATorre_Disparador>(BT.GetAIOwner()->GetPawn())->EnRango());
   
}
