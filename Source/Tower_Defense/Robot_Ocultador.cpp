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
    RealizarAnimacion(2);
    RealizarAnimacion(4);
    this->Vulnerabilizar();
    GetWorld()->GetTimerManager().SetTimer(TimerFrame, this, &ARobot_Ocultador::TrasAbrirPuntoExpuesto, this->TiempoParaAbrirCerrarPuntoExpuesto, false);               

}

void ARobot_Ocultador::TrasAbrirPuntoExpuesto() {
    Super::PrepararAtaque();
}

void ARobot_Ocultador::InicializarMover() {

    Super::ClearTimer();
    RealizarAnimacion(5); 
    GetWorld()->GetTimerManager().SetTimer(TimerFrame, this, &ARobot_Ocultador::TrasCerrarPuntoExpuesto, this->TiempoParaAbrirCerrarPuntoExpuesto, false);               





  
}

void ARobot_Ocultador::TrasCerrarPuntoExpuesto() {
    this->Invulnerabilizar();
    Super::InicializarMover();
}



void ARobot_Ocultador::Invulnerabilizar() {
    this->Vida->Vulnerable = false;


}
void ARobot_Ocultador::Vulnerabilizar() {
    this->Vida->Vulnerable = true;


}
void ARobot_Ocultador::InicializarMoverVertical() {

    RealizarAnimacion(5); 
    Super::InicializarMoverVertical();

    // En super

    /*

    Super::ClearTimer();
    this->DistanciaRecorridaVertical = 0.f;
    this->Velocidad = 750;

    RealizarAnimacion(1); // Animar el robot para que se mueva (loop)

    float DeltaTiempo = UGameplayStatics::GetWorldDeltaSeconds(this) * 1.3f;
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ARobot::MoverVertical, DeltaTiempo);
    GetWorld()->GetTimerManager().SetTimer(TimerFrame, Delegate, DeltaTiempo, true); 
    */ 
}

void ARobot_Ocultador::QuitarIA() {
    
    Super::ClearTimer();
    RealizarAnimacion(4); 
   // GetWorld()->GetTimerManager().SetTimer(TimerFrame, this, &ARobot::QuitarIA, this->TiempoParaAbrirCerrarPuntoExpuesto, false);   
    Super::QuitarIA();

    /*
    // En super
    Super::QuitarIA();

    // En los robots, al quitar IA se debe quitar la animacion de moverse tmb
    RealizarAnimacion(2); 

    */

}