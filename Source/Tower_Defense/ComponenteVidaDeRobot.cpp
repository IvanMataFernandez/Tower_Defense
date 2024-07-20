


#include "ComponenteVidaDeRobot.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode_EnPartida.h"
#include "Robot.h"



void UComponenteVidaDeRobot::BeginPlay() {
    Super::BeginPlay();

    this->Robot = Cast<ARobot> (Super::GetOwner());
}


void UComponenteVidaDeRobot::AplicarDano(AActor* Danado, float DanoBase, const UDamageType* TipoDano, AController* Instigator, AActor* Causador) {

    Super::AplicarDano(Danado, DanoBase, TipoDano, Instigator, Causador);


    float DanoAbsorbido = Super::ObtenerUltimoDanoRecibido();

    AGameMode_EnPartida* Gamemode = Cast<AGameMode_EnPartida>(GetWorld()->GetAuthGameMode());
    


    if (Gamemode) { // TODO: Quitar este check de GameMode en la version final.
        Gamemode->ProcesarDanoDeRobot(this->Robot, DanoAbsorbido);

        if (!Super::EstaVivo() && DanoAbsorbido > 0.f) {
            // En el caso de los robots, se debe procesar el hecho de que se ha muerto para contabilizar cuando spawnear siguiente oleada y procesar win con logic.
            // si el robot acaba de recibir el golpe de gracia

            Gamemode->ProcesarMuerteDeRobot(this->Robot);
        }

    } 








}



