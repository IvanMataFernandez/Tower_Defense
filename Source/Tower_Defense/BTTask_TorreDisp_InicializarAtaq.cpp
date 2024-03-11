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


    /*

    Para tareas que requieren ser ejecutadas en bucle, crear un timehandle y llamarlo cada X tiempo con parametro de entrada deltatime adecuado.
    Por ejemplo, si se llama la funcion atacar 10 veces por segundo, asignarle deltatime de 0.1

    En principio si se cancela la tarea, el timerhandler se deberia desactivar él solo también, aunque conviene probarlo

    UE_LOG(LogTemp, Display, TEXT("HELLO"));
    //BT->
    ATorre_Disparador* Pawn = Cast<ATorre_Disparador>(BT.GetAIOwner()->GetPawn());
    if (Pawn) {
    Pawn->Atacar(UGameplayStatics::GetWorldDeltaSeconds(GetWorld()));
    }

    return EBTNodeResult::InProgress;

    */

    return EBTNodeResult::Succeeded;



 }
