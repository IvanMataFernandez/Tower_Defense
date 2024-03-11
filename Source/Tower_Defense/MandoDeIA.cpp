// Fill out your copyright notice in the Description page of Project Settings.


#include "MandoDeIA.h"
#include "BehaviorTree/BehaviorTree.h"





void AMandoDeIA::SettearIA(FString Clase) {

    // TODO: If else if de las rutas de BT + hacer los BT y BTTask

    FString RutaBT;

    if (Clase.Equals(TEXT("BP_Cañon_C"))) {
        RutaBT = TEXT("/Game/Blueprints/IA/TorreDisparador/BT_TorreDisparador"); // Las rutas absolutas funcionan tambien en el juego exportado final

    } /* else if (Bla bla) { [...] }

     */
    UBehaviorTree* BT = LoadObject<UBehaviorTree>(nullptr, *RutaBT);


    if (BT) {
        RunBehaviorTree(BT);
 
    } else {
        UE_LOG(LogTemp, Warning, TEXT("No AI loaded"));
    }





}

void AMandoDeIA::BeginPlay(){
    Super::BeginPlay();
}

