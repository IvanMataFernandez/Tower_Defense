// Fill out your copyright notice in the Description page of Project Settings.


#include "MandoDeIA.h"
#include "BehaviorTree/BehaviorTree.h"
#include "ConstructoraDeBlueprints.h"




void AMandoDeIA::SettearIA(uint8 Clase, bool Torre) {




    this->BT =  ConstructoraDeBlueprints::GetConstructoraDeBlueprints()->GetBT(Clase, Torre);


    if (BT) {
     //   UE_LOG(LogTemp, Warning, TEXT("Cargando Behavior Tree para ID: %d"), Clase);

        this->RunBehaviorTree(BT);
 
    } else {
        UE_LOG(LogTemp, Warning, TEXT("No AI loaded for ID: %d"), Clase );
    }





}


void AMandoDeIA::ActivarIA(bool Activar) {
    UBehaviorTreeComponent* BehaviorTreeComponent = this->FindComponentByClass<UBehaviorTreeComponent>();

    if (Activar) {
        this->RunBehaviorTree(BT);

    } else {
        BehaviorTreeComponent->StopTree();

    }


}



