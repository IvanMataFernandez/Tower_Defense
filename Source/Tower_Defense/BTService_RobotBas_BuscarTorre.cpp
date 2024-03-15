// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_RobotBas_BuscarTorre.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Robot_Basico.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_RobotBas_BuscarTorre::TickNode(UBehaviorTreeComponent &BT, uint8 *NodeMemory, float DeltaTime) {
    Super::TickNode(BT, NodeMemory, DeltaTime);
    BT.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(),  Cast<ARobot_Basico>(BT.GetAIOwner()->GetPawn())->TorreEnRango());
   
}

