// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_TorreDisp_BuscarRobot.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Torre_Disparador.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_TorreDisp_BuscarRobot::TickNode(UBehaviorTreeComponent &BT, uint8 *NodeMemory, float DeltaTime) {
    Super::TickNode(BT, NodeMemory, DeltaTime);
    BT.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(),  Cast<ATorre_Disparador>(BT.GetAIOwner()->GetPawn())->EnRango());
   
}
