// Fill out your copyright notice in the Description page of Project Settings.


#include "Torre_Disparador.h"
#include "Components/SceneComponent.h"
#include "Proyectil.h"
#include "TimerManager.h"
#include "Robot.h"



// Toda torre que dispara proyectiles hereda de esta clase

/*

    IDs de animaciones:
    0: Morir
    1: Desapuntar
    2: Apuntar
    3: Disparar tiro 1
    n: Disparar tiro (n-2)

*/



void ATorre_Disparador::BeginPlay() {
    Super::BeginPlay();



} 



ATorre_Disparador::ATorre_Disparador() {

    // Super() se hace solo 

    this->SpawnProyectiles = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnProyectiles"));
    this->SpawnProyectiles->SetupAttachment(CuerpoBase);
}


int ATorre_Disparador::ObtenerCadenciaDeDisparo() {return this->CadenciaDeDisparo;}



// Métodos de IA:

void ATorre_Disparador::PrepararDesapuntar() {
  
    Super::ClearTimer();

    float Espera = 1.5f;  // Esperar 1,5 segundos tras no ver enemigo para apagar torre.
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ATorre_Disparador::Desapuntar);    
    Super::ProgramarTimer(Delegate, Espera, false);

}

void ATorre_Disparador::Desapuntar() {
    Super::RealizarAnimacion(1); // Desapuntar

}


bool ATorre_Disparador::EnRango() {
    
    // Realiza el line trace y devuelve si hay hit.

    FVector Start =  this->SpawnProyectiles->GetComponentLocation();
    FVector End = Start + (FVector(0,256.f+this->RangoEnCasillas*512.f,0) ); //Cada casilla son 512.f. 256.f para offsettear la casilla sobre la que está

    FHitResult HitResult;


    // Hay target si el linetrace hittea algo que ve una torre (Robot o zona de spawn de robots) y se trata de un robot (o sea, no la zona de spawn de robots en
    // la esquina de la pantalla)

    return GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_GameTraceChannel5) && Cast<ARobot>(HitResult.GetActor()) != nullptr; 



}




void ATorre_Disparador::Apuntar() {
    

    Super::RealizarAnimacion(2); // Apuntar
    Super::ProgramarTimerFinDeTareaIA(this->TiempoParaApuntar);

}

void ATorre_Disparador::AnimarDisparo(int DisparosRestantes) {
    
    // Pre: Disparos restantes indica cuantos disparos quedan por hacer en el ciclo (incluye el disparo que se va a animar ahora)

    Super::RealizarAnimacion((this->CadenciaDeDisparo-DisparosRestantes)+3); // Animar el disparo
    Super::ProgramarTimerFinDeTareaIA(this->TiempoAnimarDisparo);


}


void ATorre_Disparador::Disparar() {

    // Hacer aparecer el proyectil en el spawnpoint de proyectiles. El proyectil en sí se mueve con su lógica en su código

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; // Forzar al proyectil a que aparezca (por si justo se pone la torre encima de un robot)
    AProyectil* Proyectil = AActor::GetWorld()->SpawnActor<AProyectil>(this->ClaseBlueprintProyectil, this->SpawnProyectiles->GetComponentLocation(), SpawnProyectiles->GetComponentRotation(),SpawnParams);


    Super::ProgramarTimerFinDeTareaIA(this->TiempoDisparo);

}

void ATorre_Disparador::EsperaFinDeCicloDeAtaque() {
    
    Super::ProgramarTimerFinDeTareaIA(this->TiempoDeCiclo - this->CadenciaDeDisparo * (this->TiempoAnimarDisparo + this->TiempoDisparo));

}
