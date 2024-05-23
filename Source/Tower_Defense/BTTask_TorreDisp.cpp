// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TorreDisp.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Torre_Disparador.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


/*
    Instrucciones posibles:
        - Apuntar
        - Animar disparo
        - Disparar
        - Esperar y recargar
        - Desapuntar



*/



UBTTask_TorreDisp::UBTTask_TorreDisp() {
      NodeName = "TorreDisp";

}

 EBTNodeResult::Type UBTTask_TorreDisp::ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) {

      Super::ExecuteTask(BT,NodeMemory);
      ATorre_Disparador* Torre = Cast<ATorre_Disparador>(BT.GetAIOwner()->GetPawn());

      switch (this->IdInstruccion) {

            case 0:
                  Torre->Apuntar();
                  BT.GetBlackboardComponent()->SetValueAsInt(TEXT("DisparosRestantes"), Torre->ObtenerCadenciaDeDisparo());

                  return EBTNodeResult::InProgress;


            case 1:
                  Torre->AnimarDisparo(BT.GetBlackboardComponent()->GetValueAsInt(TEXT("DisparosRestantes")));
                  return EBTNodeResult::InProgress;
            case 2:
                  Torre->Disparar();
                  BT.GetBlackboardComponent()->SetValueAsInt(TEXT("DisparosRestantes"), BT.GetBlackboardComponent()->GetValueAsInt(TEXT("DisparosRestantes"))-1);

                  return EBTNodeResult::InProgress;
            case 3:
                  Torre->EsperaFinDeCicloDeAtaque();
                  BT.GetBlackboardComponent()->SetValueAsInt(TEXT("DisparosRestantes"), Torre->ObtenerCadenciaDeDisparo());

                  return EBTNodeResult::InProgress;
            case 4:
                  Torre->PrepararDesapuntar();
                  return EBTNodeResult::InProgress;
      }

      return EBTNodeResult::Failed;


 }









    



