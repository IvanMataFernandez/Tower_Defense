// Fill out your copyright notice in the Description page of Project Settings.


#include "Torre.h"
#include "Entidad.h"
#include "GameFramework/Actor.h"
#include "Casilla.h"
#include "MandoDeIA.h"


// Toda torre implementa esta clase.

void ATorre::ProcesarFinDeVida() {
    
    // Si la torre llega a su fin... Quitarla de la casilla ocupada antes de destruirla del motor de juego y animar su muerte

    ACasilla* Casilla = Cast<ACasilla>(AActor::GetOwner());


    if (Casilla) {   // TODO: Cambiar esto en producto final. Esto es un workaround para que no crashee el programa con torres colocadas encima de casillas en el motor de juego sin pinchar en ellas (Lo mismo en quitar torre)
        Casilla->QuitarReferenciaTorre();
    }   



    Super::ProcesarFinDeVida(); // Después, se puede matar la torre (animando esto y destruyendola del motor de juego)

}



