// Fill out your copyright notice in the Description page of Project Settings.


#include "MandoDeIA.h"
#include "BehaviorTree/BehaviorTree.h"





void AMandoDeIA::SettearIA(FString Clase) {

    // TODO: If else if de las rutas de BT + hacer los BT y BTTask

    FString RutaBT;
    UE_LOG(LogTemp, Display, TEXT("%s"),*Clase);
    if (Clase.Equals(TEXT("BP_Cañon_C")) || Clase.Equals(TEXT("BP_CañonDoble_C")) || Clase.Equals(TEXT("BP_PistolaLaser_C"))) {
        RutaBT = TEXT("/Game/Blueprints/IA/TorreDisparador/BT_TorreDisparador"); // Las rutas absolutas funcionan tambien en el juego exportado final

    } /* else if (Bla bla) { [...] }

     */
    UBehaviorTree* BT = LoadObject<UBehaviorTree>(nullptr, *RutaBT);
    UE_LOG(LogTemp, Display, TEXT("Cargando Behavior Tree para la clase: %s"), *Clase);


    if (BT) {
        RunBehaviorTree(BT);
 
    } else {
        UE_LOG(LogTemp, Warning, TEXT("No AI loaded"));
    }





}

void AMandoDeIA::BeginPlay(){
    Super::BeginPlay();
}

