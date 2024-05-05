// Fill out your copyright notice in the Description page of Project Settings.


#include "Torre_Muro.h"


/*

    IDs de animaciones:
   -2: Mostrar estado 2 vida
   -1: Mostrar estado 1 vida 
    0: Morir
    1: Empezar Idle
    2: Parar Idle

*/

void ATorre_Muro::BeginPlay() {
    Super::BeginPlay();
    this->RealizarAnimacion(1);
}


void ATorre_Muro::Matar() {
    
    this->RealizarAnimacion(2);
    Super::Matar();

}
