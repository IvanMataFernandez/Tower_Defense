// Fill out your copyright notice in the Description page of Project Settings.


#include "Torre_UsoUnico.h"
#include "Components/BoxComponent.h"
#include "ComponenteVida.h"
#include "Kismet/GameplayStatics.h"

#include "MandoDeIA.h"

/*

    Toda torre que solo tenga un uso antes de autodestruirse hereda de aquí. Puede ser instakills o torres que se queden un rato mas hasta que algo pase

    IDs de animaciones:

    0: Morir (solo activable si muere de verdad y no "muere" porque se ha activado y hecho su uso único)
    1: Activar Detonación


*/


ATorre_UsoUnico::ATorre_UsoUnico() {

    // super() se hace solo
    this->ZonaDeAfecto = CreateDefaultSubobject<UBoxComponent>(TEXT("ZonaDeAfecto"));
    this->ZonaDeAfecto->SetupAttachment(RootComponent);
}




void ATorre_UsoUnico::InicializacionFuncion() {


    // Programar el timer de para que aplique el daño de explosion a los X segundos

    float Espera =  this->TiempoParaExplosion;
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ATorre_UsoUnico::HacerFuncion);    
    Super::ProgramarTimer(Delegate, Espera, false);

    Super::RealizarAnimacion(1); // Animar detonación

}



void ATorre_UsoUnico::Activar() {
    // En principio dañar aquí, pero si se quieren hacer otras funciones en un area, entonces hacer esto Virtual y heredar de esta clase

    // Por defecto hace BOOM! Pero se puede heredar de esta clase e implementar este metodo despues si se necesitan usos instantaneos que no hagan daño.
    // Si hacen daño con un efecto añadido, se puede considerar heredar de aqui. Para ello dividir buscar targets y dañar en dos metodos aparte


    // Encontrar targets y dañarlos

    TArray<FOverlapResult> Resultado;
    FComponentQueryParams QueryParams;

    // Para que encuentre target debe primero encontrar el trace (usando el canal 5) y luego el campo y el target deben ser al menos overlappeables respecto a colision fisica
    this->ZonaDeAfecto->ComponentOverlapMulti(Resultado, GetWorld(), AActor::GetActorLocation(), AActor::GetActorRotation(), ECollisionChannel::ECC_GameTraceChannel5, QueryParams);



    for (FOverlapResult Objeto : Resultado) {
        AActor* Actor = Objeto.GetActor();
	    UGameplayStatics::ApplyDamage(Actor, this->DanoDeExplosion, nullptr, this, UDamageType::StaticClass());




    }


    Super::ProcesarFinDeVida(); // La torre desaparece tras hacer su función

}



void ATorre_UsoUnico::AutoDestruir() {


    // Ocultar la entidad offscreen para que suene el SFX. PRogramar timer para que se destruya del motor de juego tras que finalice su SFX.

    Super::AutoDestruir();

    float Espera =  this->TiempoDeExplosion;
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ATorre_UsoUnico::Destruir);    
    Super::ProgramarTimer(Delegate, Espera, false);

}


// Métodos de IA:

void ATorre_UsoUnico::HacerFuncion() {
    this->Activar();

}


