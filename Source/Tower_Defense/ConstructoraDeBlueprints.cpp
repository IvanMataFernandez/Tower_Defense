// Fill out your copyright notice in the Description page of Project Settings.


#include "ConstructoraDeBlueprints.h"
#include "BehaviorTree/BehaviorTree.h"


#include "Torre.h"


// MAE que se encarga de coger los paths de los blueprints y darselos a otras clases

// Si se cambia algun path de los blueprints, solo es necesario editarlo aquí

ConstructoraDeBlueprints ConstructoraDeBlueprints::Objeto = ConstructoraDeBlueprints();
ConstructoraDeBlueprints::ConstructoraDeBlueprints() {}
ConstructoraDeBlueprints::~ConstructoraDeBlueprints() {}



ConstructoraDeBlueprints* ConstructoraDeBlueprints::GetConstructoraDeBlueprints() {
    return &ConstructoraDeBlueprints::Objeto;

}


UBehaviorTree* ConstructoraDeBlueprints::GetBT(uint8 Clase) {
   
    // Dada la Ruta (clase) que se quiere usar, obtener su BT en blueprint correspondiente

    FString RutaBT;

    switch (Clase) {
        case Rutas::Canon:
        case Rutas::CanonDoble:
        case Rutas::PistolaLaser:
            RutaBT = TEXT("/Game/Blueprints/IA/Torres/TorreDisparador/BT_TorreDisparador");

            break;

        case Rutas::PanelSolar:
        case Rutas::PanelSolarDoble:
            RutaBT = TEXT("/Game/Blueprints/IA/Torres/TorreProducidor/BT_TorreProducidor");

            break;
        
        case Rutas::Bomba:
            RutaBT = TEXT("/Game/Blueprints/IA/Torres/TorreUsoInstantaneo/BT_TorreUsoInstantaneo"); 

    }

    return LoadObject<UBehaviorTree>(nullptr, *RutaBT);


}




