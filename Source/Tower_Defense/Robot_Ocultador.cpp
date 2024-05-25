// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot_Ocultador.h"
#include "ComponenteVidaConEstados.h"


// El robot ocultador implementa esta clase

/*

    IDs de animaciones:
   -1: Mostrar estado 1 vida (dañado)
    0: Morir
    1: Moverse
    2: Parar de moverse
    3: Disparar laser
    4: Abrir punto expuesto
    5: Ocultar punto expuesto

*/

void ARobot_Ocultador::BeginPlay() {
    Super::BeginPlay();

}



// Métodos de IA:

void ARobot_Ocultador::Ocultar() {

    // Realiza la animación de ocultar y se settea como invencible tras acabar dicha animación

    Super::RealizarAnimacion(5);

    // Esperar a que el robot se oculte para flaggearlo como invencible
    float Espera = this->TiempoParaAbrirCerrarPuntoExpuesto;
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ARobot_Ocultador::FinalizarOcultacion);    
    Super::ProgramarTimer(Delegate, Espera, false);

}

void ARobot_Ocultador::FinalizarOcultacion() {

    Super::SetVulnerable(false);
    Super::ProgramarTimerFinDeTareaIA(0);
}


void ARobot_Ocultador::Desocultar() {

    // Realiza la animación de desocultar y el momento en el que empieza a hacerla se settea como vulnerable

    Super::SetVulnerable(true);
    Super::RealizarAnimacion(4);
	Super::ProgramarTimerFinDeTareaIA(this->TiempoParaAbrirCerrarPuntoExpuesto); 

}

