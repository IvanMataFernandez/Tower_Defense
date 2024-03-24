// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot_Bomba.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ComponenteVida.h"


/*

    IDs de animaciones:
   -1: Mover ruedas (quitar loop)
    0: Morir
    1: Mover ruedas (activar loop)
    2: Disparar laser
    3: Detonar

*/


ARobot_Bomba::ARobot_Bomba() {
    this->AreaDeExplosion = CreateDefaultSubobject<UBoxComponent>(TEXT("RangoDeExplosion"));
    this->AreaDeExplosion->SetupAttachment(PosicionBase);
}

void ARobot_Bomba::Matar() {

    this->EmpezarDetonar();


}
void ARobot_Bomba::EmpezarDetonar() { 

    // Desactivar el robot para que no haga nada mientras detona

    Super::ClearTimer(); // Quitar la subrutina de disparo
    UComponenteVida* ComponenteVida = FindComponentByClass<UComponenteVida>(); // Hacer al robot invulnerable durante la explosión para que no pueda detonar dos veces seguidas
    ComponenteVida->Vulnerable = false;

    Velocidad = 0;
    float Espera = this->TiempoParaExplosion;
    
    RealizarAnimacion(-1); // Quitar el loop de animacion de movimiento de ruedas
    RealizarAnimacion(3);
    // Animar el robot para que detone
    GetWorld()->GetTimerManager().SetTimer(TimerFrame, this, &ARobot_Bomba::Detonar,Espera, false);


}

void ARobot_Bomba::Detonar() {
    

    // Encontrar targets y dañarlos

    TArray<FOverlapResult> Resultado;
    FComponentQueryParams QueryParams;

    // Para que encuentre target debe primero encontrar el trace (usando el canal 6) y luego el campo y el target deben ser al menos overlappeables respecto a colision fisica
    this->AreaDeExplosion->ComponentOverlapMulti(Resultado, GetWorld(), AActor::GetActorLocation(), AActor::GetActorRotation(), ECollisionChannel::ECC_GameTraceChannel6, QueryParams);



    for (FOverlapResult Objeto : Resultado) {
        AActor* Actor = Objeto.GetActor();
	    UGameplayStatics::ApplyDamage(Actor, this->DanoDeExplosion, nullptr, this, UDamageType::StaticClass());
    }

    Super::Matar();


}
