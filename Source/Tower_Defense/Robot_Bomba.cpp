// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot_Bomba.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


// TODO: Crear robot bomba radar heredando de esta clase. Solo requiere la funcionalidad adicional de scannear si hay X torres en su rango. Esta clase ya sabe detonar y matar torres


ARobot_Bomba::ARobot_Bomba() {
    this->AreaDeExplosion = CreateDefaultSubobject<UBoxComponent>(TEXT("RangoDeExplosion"));
    this->AreaDeExplosion->SetupAttachment(PosicionBase);
}

void ARobot_Bomba::Matar() {

    this->Detonar();

    Super::Matar();

}

void ARobot_Bomba::Detonar() {
    
    // Desactivar el robot para que no haga nada mientras detona

    Super::ClearTimer(); // Quitar la subrutina de disparo
    Velocidad = 0;

    // TODO: Animar aquí la explosión

    // Considerar hacer un WAIT Aqui mediante Timer y llamar a la funcion despues. O hacer que el componente de animacion vuelva aquí tras animar.


    // Encontrar targets y dañarlos

    TArray<FOverlapResult> Resultado;
    FComponentQueryParams QueryParams;

    // Para que encuentre target debe primero encontrar el trace (usando el canal 6) y luego el campo y el target deben ser al menos overlappeables respecto a colision fisica
    this->AreaDeExplosion->ComponentOverlapMulti(Resultado, GetWorld(), AActor::GetActorLocation(), AActor::GetActorRotation(), ECollisionChannel::ECC_GameTraceChannel6, QueryParams);



    for (FOverlapResult Objeto : Resultado) {
        AActor* Actor = Objeto.GetActor();
	    UGameplayStatics::ApplyDamage(Actor, this->DanoDeExplosion, nullptr, this, UDamageType::StaticClass());


        UE_LOG(LogTemp, Warning, TEXT("%s empezó a solapar con %s en el canal de colisión específico."), *GetName(), *Actor->GetName());


    }

}
