// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot_Bomba.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"



// Todo robot con forma de bomba que puede detonar al morir forma parte de esta clase

/*

    IDs de animaciones:
   -2: Mostrar estado 2 vida (dañado)
   -1: Mostrar estado 1 vida  (muy dañado)
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





void ARobot_Bomba::ProcesarFinDeVida() {

    // Antes de empezar a detonar, quitar la hitbox al robot. Esta es la primera instrucción ejecutada cuando se da la orden de eliminar el robot

    Super::DesactivarHitbox();
    Super::ProcesarFinDeVida();

}


void ARobot_Bomba::Matar() {

    // Una vez quitada la hitbox y los enlaces a los bots de la cola, se puede empezar a detonar

    this->EmpezarDetonar();


}
void ARobot_Bomba::EmpezarDetonar() { 

    // Desactivar el robot para que no haga nada mientras detona

    Super::QuitarIA(); // Desactivar la IA y sus timers asociados
    Super::SetVulnerable(false); // Hacer al robot invulnerable durante la explosión para que no pueda detonar dos veces seguidas
    
    Super::RealizarAnimacion(2); // Quitar el loop de animacion de movimiento de ruedas
    Super::RealizarAnimacion(4); // Animar la detonación


    // Esperar a que la animación acabe para detonar y calcular el daño
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

    
    
    // Por cada target encontrado, dañarlo aplicando el daño de explosion

    for (FOverlapResult Objeto : Resultado) {
        AActor* Actor = Objeto.GetActor();
	    UGameplayStatics::ApplyDamage(Actor, this->DanoDeExplosion, nullptr, this, UDamageType::StaticClass());
    }


    // Finalmente, se puede quitar visualmente del nivel (primero se hace AutoDestruir() antes de DEstroy())

    Super::Matar();




}


void ARobot_Bomba::AutoDestruir() {


    Super::AutoDestruir();  // Mover la entidad offscreen

    // Esperar el tiempo de explosion para que el SFX acabe de sonar para poder destruir la instancia completamente

    float Espera = this->TiempoDeExplosion;
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ARobot_Bomba::Destruir);    
    Super::ProgramarTimer(Delegate, Espera, false);


}