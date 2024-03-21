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
                RutaBT = TEXT("/Game/Blueprints/IA/Robots/RobotBombaRadar/BT_RobotBombaRadar");  // TEXT("/Game/Blueprints/IA/Robots/RobotBasico/BT_RobotBasico"); 

        }      
        // Robots


    }



    return LoadObject<UBehaviorTree>(nullptr, *RutaBT);


}



float ConstructoraDeBlueprints::GetTiempoDeRecargaDeTorre(uint8 Clase) {
        switch (Clase) {
            case Torres::Canon:
            case Torres::CanonDoble:
            case Torres::PistolaLaser:
                return 5.f;
                


            case Torres::PanelSolar:
            case Torres::PanelSolarDoble:
                return 3.f;
            
            case Torres::Bomba:
                return 25.f;

        }
    
     return 999.f;

}
int ConstructoraDeBlueprints::GetCosteDeTorre(uint8 Clase) {
        switch (Clase) {
            case Torres::Canon:
                return 20;
            case Torres::CanonDoble:
                return 45;
            case Torres::PistolaLaser:
                return 55;
                


            case Torres::PanelSolar:
                return 10;
            case Torres::PanelSolarDoble:
                return 25;
            
            case Torres::Bomba:
                return 35;

        }

        return 999;
}

int ConstructoraDeBlueprints::GetPesoDeRobot(uint8 Clase) {

          switch (Clase) {
            case Robots::Basico:
                return 1;
            case Robots::Bomba:
                return 3;
            
            case Robots::BombaRadar:
                return 4;

        }  

        return 99;

}
