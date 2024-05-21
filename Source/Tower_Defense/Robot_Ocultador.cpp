// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot_Ocultador.h"
#include "ComponenteVidaConEstados.h"

/*

    IDs de animaciones:
   -1: Mostrar estado 1 vida 
    0: Morir
    1: Moverse
    2: Parar de moverse
    3: Disparar laser
    4: Abrir punto expuesto
    5: Ocultar punto expuesto

*/

void ARobot_Ocultador::BeginPlay() {
    Super::BeginPlay();
    this->Vida = FindComponentByClass<UComponenteVidaConEstados>();

}

void ARobot_Ocultador::InicializarAtaque() {

    // Reimplementar Inicializar ataque para poder syncear bien las animaciones y vulnerabilizar el robot

    Super::ClearTimer();
    Super::RealizarAnimacion(2);
    Super::RealizarAnimacion(4);
    this->Vida->Vulnerabilizar();


    float Espera = this->TiempoParaAbrirCerrarPuntoExpuesto;
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ARobot_Ocultador::TrasAbrirPuntoExpuesto);    
    Super::ProgramarTimer(Delegate, Espera, false);

}

void ARobot_Ocultador::TrasAbrirPuntoExpuesto() {
    Super::PrepararAtaque();
}

void ARobot_Ocultador::InicializarMover() {

    Super::ClearTimer();
    Super::RealizarAnimacion(5); 


    float Espera = this->TiempoParaAbrirCerrarPuntoExpuesto;
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ARobot_Ocultador::TrasCerrarPuntoExpuesto);    
    Super::ProgramarTimer(Delegate, Espera, false);
    
  
}

void ARobot_Ocultador::TrasCerrarPuntoExpuesto() {
    this->Vida->Invulnerabilizar();
    Super::InicializarMover();
}



void ARobot_Ocultador::InicializarMoverVertical() {

    RealizarAnimacion(5); 
    Super::InicializarMoverVertical();

}

void ARobot_Ocultador::QuitarIA() {
    
    Super::ClearTimer();
    RealizarAnimacion(4); 

    Super::QuitarIA();


}