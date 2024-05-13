// Fill out your copyright notice in the Description page of Project Settings.


#include "Torre_UsoUnico.h"
#include "Components/BoxComponent.h"
#include "ComponenteVida.h"
#include "Kismet/GameplayStatics.h"

#include "MandoDeIA.h"

/*

    Toda torre que solo tenga un uso antes de autodestruirse hereda de aquí. Puede ser instakills o torres que se queden un rato mas hasta que algo pase

    IDs de animaciones:

    0: Morir (unused)
    1: Activar Detonación


*/


ATorre_UsoUnico::ATorre_UsoUnico() {

    // super() se hace solo
    this->ZonaDeAfecto = CreateDefaultSubobject<UBoxComponent>(TEXT("ZonaDeAfecto"));
    this->ZonaDeAfecto->SetupAttachment(PosicionBase);
}


void ATorre_UsoUnico::BeginPlay() {
    Super::BeginPlay();

    // Algunas torres son de uso instaneo que heredan de esta, estas clases no tienen componente de vida por lo que no mueren de forma tradicional
    // en su lugar, se matan tras hacer su funcion


}

void ATorre_UsoUnico::InicializacionFuncion() {





    float Espera = this->TiempoParaExplosion;
    GetWorld()->GetTimerManager().SetTimer(TimerFrame, this, &ATorre_UsoUnico::HacerFuncion,Espera, false);
    RealizarAnimacion(1); // Animar detonación

}

void ATorre_UsoUnico::HacerFuncion() {
    this->Activar();

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




    Super::Matar(); // La torre desaparece tras hacer su función

}



void ATorre_UsoUnico::AutoDestruir() {
    Super::AutoDestruir();
    GetWorld()->GetTimerManager().SetTimer(TimerFrame, this, &ATorre_UsoUnico::Destruir, this->TiempoDeExplosion, false);

}