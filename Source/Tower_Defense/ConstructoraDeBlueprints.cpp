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


UBehaviorTree* ConstructoraDeBlueprints::GetBT(uint8 Clase, bool Torre) {
   
    // Dada la Ruta (clase) que se quiere usar, obtener su BT en blueprint correspondiente

    FString RutaBT;


    if (Torre) {

        // Torres

        switch (Clase) {
            case Torres::Canon:
            case Torres::CanonDoble:
            case Torres::PistolaLaser:
                RutaBT = TEXT("/Game/Blueprints/IA/Torres/TorreDisparador/BT_TorreDisparador");

                break;

            case Torres::PanelSolar:
            case Torres::PanelSolarDoble:
                RutaBT = TEXT("/Game/Blueprints/IA/Torres/TorreProducidor/BT_TorreProducidor");

                break;
            
            case Torres::Bomba:
                RutaBT = TEXT("/Game/Blueprints/IA/Torres/TorreUsoInstantaneo/BT_TorreUsoInstantaneo"); 

        }
    } else {

          switch (Clase) {
            case Robots::Basico:
            case Robots::Bomba:
                RutaBT = TEXT("/Game/Blueprints/IA/Robots/RobotBasico/BT_RobotBasico"); 

                break;
            
            case Robots::BombaRadar:
                RutaBT = TEXT("");  // TEXT("/Game/Blueprints/IA/Robots/RobotBasico/BT_RobotBasico"); 

        }      
        // Robots


    }



    return LoadObject<UBehaviorTree>(nullptr, *RutaBT);


}




