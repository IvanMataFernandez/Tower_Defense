// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Robot_MirarDistVerti.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Robot.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_Robot_MirarDistVerti::TickNode(UBehaviorTreeComponent &BT, uint8 *NodeMemory, float DeltaTime) {
    Super::TickNode(BT, NodeMemory, DeltaTime);
    BT.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(),  Cast<ARobot>(BT.GetAIOwner()->GetPawn())->HaMovidoEnVerticalDistanciaX(this->Distancia));
   
}
