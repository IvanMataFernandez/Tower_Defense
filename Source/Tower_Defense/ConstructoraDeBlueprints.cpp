// Fill out your copyright notice in the Description page of Project Settings.


#include "ConstructoraDeBlueprints.h"
#include "BehaviorTree/BehaviorTree.h"


#include "Torre.h"


// MAE que se encarga de coger los paths de los blueprints y darselos a otras clases, también almacena variables estáticas de clases blueprint
// (porque las clases blueprint no pueden tener atributos estáticos)

/*
    Los atributos estáticos en cuestión son:

    Por cada tipo de torre blueprint (panel, cañón, cañón doble...)
        - Su coste
        - Su tiempo de recarga
        - Si debería aparecer ya recargada o no al principio del nivel

    Por cada robot:
        - Su peso en oleada


    Los paths de blueprint que maneja:

        - Los BehaviorTrees que cada entidad debe usar
        - Las texturas de los iconos de las torres (solo disponible para torres)

*/


ConstructoraDeBlueprints ConstructoraDeBlueprints::Objeto = ConstructoraDeBlueprints();
ConstructoraDeBlueprints::ConstructoraDeBlueprints() {}
ConstructoraDeBlueprints::~ConstructoraDeBlueprints() {}



ConstructoraDeBlueprints* ConstructoraDeBlueprints::GetConstructoraDeBlueprints() {
    return &ConstructoraDeBlueprints::Objeto;

}


UBehaviorTree* ConstructoraDeBlueprints::GetBT(uint8 Clase, bool Torre) const {
   
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
            case Torres::Mina:
                RutaBT = TEXT("/Game/Blueprints/IA/Torres/Mina/BT_Mina");
                break;

            case Torres::Bomba:
                RutaBT = TEXT("/Game/Blueprints/IA/Torres/TorreUsoInstantaneo/BT_TorreUsoInstantaneo"); 
                break;
            case Torres::Escudo:
                return nullptr;


        }
    } else {
        // Robots

          switch (Clase) {
            case Robots::Basico:
            case Robots::LiderOleada:
            case Robots::Medio:
            case Robots::Duro:
            case Robots::Bomba:

                RutaBT = TEXT("/Game/Blueprints/IA/Robots/RobotBasico/BT_RobotBasico"); 

                break;
            
            case Robots::BombaRadar:
                RutaBT = TEXT("/Game/Blueprints/IA/Robots/RobotBombaRadar/BT_RobotBombaRadar");  
                break;


            case Robots::Ocultador:
                RutaBT = TEXT("/Game/Blueprints/IA/Robots/RobotOcultador/BT_RobotOcultador");  
                break;

            case Robots::Preview:    
                RutaBT = TEXT("/Game/Blueprints/IA/Robots/Preview/BT_Preview");  
                

        }      


    }



    return LoadObject<UBehaviorTree>(nullptr, *RutaBT);


}



float ConstructoraDeBlueprints::GetTiempoDeRecargaDeTorre(uint8 Clase) const {
        switch (Clase) {
            case Torres::Canon:
            case Torres::PistolaLaser:
            case Torres::PanelSolar:
            case Torres::CanonDoble:
            case Torres::PanelSolarDoble:

                return 5.f;
                


            
            case Torres::Mina:
            case Torres::Bomba:
            case Torres::Escudo:
                return 25.f;

        }
    
     return 999.f;

}


bool ConstructoraDeBlueprints::GetEmpiezaRecargadaTorre(uint8 Clase) const {


    return Clase >= 8 && Clase <= 10;
}

int ConstructoraDeBlueprints::GetCosteDeTorre(uint8 Clase) const {
        switch (Clase) {
            case Torres::Canon:
                return 50;
            case Torres::CanonDoble:
                return 100;
            case Torres::PistolaLaser:
                return 110;
                


            case Torres::PanelSolar:
            case Torres::Escudo:

                return 20;
            case Torres::PanelSolarDoble:
                return 35;
            
            case Torres::Mina:
                return 10;

            case Torres::Bomba:
                return 70;

        }

        return 999;
}



int ConstructoraDeBlueprints::GetPesoDeRobot(uint8 Clase) const {

          switch (Clase) {
            case Robots::Basico:
            case Robots::LiderOleada:
                return 1;
            case Robots::Medio:
            case Robots::Bomba:

                return 2;
            case Robots::Ocultador:
            case Robots::Duro:

                return 3;
            
            case Robots::BombaRadar:


                return 4;


        }  
        return 99;

}

bool ConstructoraDeBlueprints::TorrePermiteOverlappearRobot(int ID) const {
    return ID == 12; // Solo instant kills se pueden poner justo en el camino de un robot. La unica instant kill en este juego es la bomba (ID = 12)
}


UTexture2D* ConstructoraDeBlueprints::ObtenerImagenDeTorre(int ID) const {
    

        FString Ruta = TEXT("/Game/Assets/Texturas/Torre") + FString::Printf(TEXT("%d"), ID);
        return LoadObject<UTexture2D>(nullptr, *Ruta);

    
}




