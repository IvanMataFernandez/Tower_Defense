// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TorreDisp_Atacar.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Torre_Disparador.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "TimerManager.h"
#include "Engine/EngineTypes.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_TorreDisp_Atacar::UBTTask_TorreDisp_Atacar() {
      NodeName = "TorreDisp_InicializarAtacar";

}

 EBTNodeResult::Type UBTTask_TorreDisp_Atacar::ExecuteTask(UBehaviorTreeComponent &BT, uint8 *NodeMemory) {

    Super::ExecuteTask(BT,NodeMemory);



   /**

    Para tareas que requieren ser ejecutadas en bucle, crear un timehandle y llamarlo cada X tiempo con parametro de entrada deltatime adecuado.
    Por ejemplo, si se llama la funcion atacar 10 veces por segundo, asignarle deltatime de 0.1 
    
    Por defecto al fracasar el timer NO PARA. Buscar el nodo en el servicio si se requiere pararlo. Estático NO va con multiples torres del mismo tipo
    poeque comparten el timer.

   

    
    
    
    
    */

    //BT->
    Cast<ATorre_Disparador>(BT.GetAIOwner()->GetPawn())->Atacar(this->FrameRate);







    return EBTNodeResult::InProgress;

    




 }