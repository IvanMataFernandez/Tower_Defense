// Fill out your copyright notice in the Description page of Project Settings.


#include "MandoDeIA.h"
#include "BehaviorTree/BehaviorTree.h"
#include "ConstructoraDeBlueprints.h"




void AMandoDeIA::SettearIA(uint8 Clase) {




    UBehaviorTree* BT =  ConstructoraDeBlueprints::GetConstructoraDeBlueprints()->GetBT(Clase);


    if (BT) {
        UE_LOG(LogTemp, Display, TEXT("Cargando Behavior Tree para ID: %d"), Clase);

        RunBehaviorTree(BT);
 
    } else {
        UE_LOG(LogTemp, Warning, TEXT("No AI loaded for ID: %d"), Clase );
    }





}

void AMandoDeIA::BeginPlay(){
    Super::BeginPlay();
}

