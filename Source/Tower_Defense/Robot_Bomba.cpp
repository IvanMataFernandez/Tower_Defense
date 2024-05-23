// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot_Bomba.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


/*

    IDs de animaciones:
   -2: Mostrar estado 2 vida
   -1: Mostrar estado 1 vida 
    0: Morir
    1: Moverse
    2: Parar de moverse
    3: Disparar laser
    4: Detonar



*/


ARobot_Bomba::ARobot_Bomba() {
    this->AreaDeExplosion = CreateDefaultSubobject<UBoxComponent>(TEXT("RangoDeExplosion"));
    this->AreaDeExplosion->SetupAttachment(RootComponent);
}

void ARobot_Bomba::Matar() {

    this->EmpezarDetonar();


}
void ARobot_Bomba::EmpezarDetonar() { 

    // Desactivar el robot para que no haga nada mientras detona

    Super::QuitarIA(); // Desactivar la IA y sus timers asociados
    Super::SetVulnerable(false); // Hacer al robot invulnerable durante la explosión para que no pueda detonar dos veces seguidas
    
    RealizarAnimacion(2); // Quitar el loop de animacion de movimiento de ruedas
    RealizarAnimacion(4);


    // Animar el robot para que detone
    float Espera = this->TiempoParaExplosion;
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ARobot_Bomba::Detonar);    
    Super::ProgramarTimer(Delegate, Espera, false);

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


void ARobot_Bomba::AutoDestruir() {
    Super::AutoDestruir();

    float Espera = this->TiempoDeExplosion;
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ARobot_Bomba::Destruir);    
    Super::ProgramarTimer(Delegate, Espera, false);


}