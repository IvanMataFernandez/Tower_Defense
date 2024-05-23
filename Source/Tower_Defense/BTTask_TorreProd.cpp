// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TorreProd.h"
#include "Torre_Producidor.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "AIController.h"


/*
    Instrucciones posibles:
        0: Cooldown (espera entre producciones)
        1: Producir (Ilumniar el panel, esperar a click de player)
        2: Fin Produccion (Tras click del player, Apagar el panel)


*/


UBTTask_TorreProd::UBTTask_TorreProd() {
      NodeName = "Productor";

}

 EBTNodeResult::Type UBTTask_TorreProd::ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) {

      Super::ExecuteTask(BT,NodeMemory);
      ATorre_Producidor* Torre = Cast<ATorre_Producidor>(BT.GetAIOwner()->GetPawn());

      switch(this->IdInstruccion) {
      case 0:
            Torre->PrepararParaProduccion();
            return EBTNodeResult::InProgress;
      case 1:
            Torre->Producir();
            return EBTNodeResult::InProgress;
      case 2:
            Torre->FinProduccion();
            return EBTNodeResult::Succeeded;


      }

      return EBTNodeResult::Failed;


 }

