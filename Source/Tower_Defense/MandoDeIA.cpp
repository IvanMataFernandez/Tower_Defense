// Fill out your copyright notice in the Description page of Project Settings.


#include "MandoDeIA.h"
#include "BehaviorTree/BehaviorTree.h"
#include "ConstructoraDeBlueprints.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"


// La clase que maneja la IA de Entidades. A toda entidad se le da esta clase como IA.


void AMandoDeIA::SettearIA(uint8 Clase, bool Torre) {


    // Al principio de crear la entidad, se le requiere cargar su Behavior Tree adecuado. Obtenerlo basado en el ID de la Entidad y si es una Torre o Robot
    

    this->BT =  ConstructoraDeBlueprints::GetConstructoraDeBlueprints()->GetBT(Clase, Torre);


    if (BT) {

        // Si tiene un BT asociado, runnearlo ya. (No todas las entidades requieren BT, las torres protectoras solo son muros que se quedan quietos y ya)
        this->RunBehaviorTree(BT);
 
    } 



}

bool AMandoDeIA::TieneIA() {
    return this->BT != nullptr;
}

void AMandoDeIA::ActivarIA(bool Activar) {

    // Post: Activar / Desactivar la IA (sin eliminarla completamente), segun el bool indicado

    if (Activar) {
        this->RunBehaviorTree(BT);

    } else {
        UBehaviorTreeComponent* BehaviorTreeComponent = this->FindComponentByClass<UBehaviorTreeComponent>();
        BehaviorTreeComponent->StopTree();

    }


}

void AMandoDeIA::AcabarTareaActual() {

    // Marcar la tarea actual del BT como completada, para que salte a la siguiente de la secuencia

    UBehaviorTreeComponent* BehaviorTreeComponent = this->FindComponentByClass<UBehaviorTreeComponent>();
    Cast<UBTTaskNode>(BehaviorTreeComponent->GetActiveNode())->FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::Succeeded);
}



void AMandoDeIA::SettearBoolEnBlackboard(FName Key, bool Valor) {

    // Settear un valor booleano en su blackboard según la clave indicada

    this->FindComponentByClass<UBehaviorTreeComponent>()->GetBlackboardComponent()->SetValueAsBool(Key, Valor);
}
/*
bool AMandoDeIA::GetBoolDeBlackboard(FName Key) {

    // Obtener un valor booleano en su blackboard según la clave indicada

    return this->FindComponentByClass<UBehaviorTreeComponent>()->GetBlackboardComponent()->GetValueAsBool(Key);
}
*/