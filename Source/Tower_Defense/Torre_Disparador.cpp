// Fill out your copyright notice in the Description page of Project Settings.


#include "Torre_Disparador.h"
#include "Components/SceneComponent.h"
#include "Proyectil.h"
#include "TimerManager.h"
#include "Robot.h"

#include "DrawDebugHelpers.h"

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


    this->EnRango();

} 



ATorre_Disparador::ATorre_Disparador() {

    // Super() se hace solo 

    this->SpawnProyectiles = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnProyectiles"));
    this->SpawnProyectiles->SetupAttachment(CuerpoBase);
}

void ATorre_Disparador::PrepararIdle() {
  
    Super::ClearTimer();

    float Espera = 1.5f;  // Esperar 1,5 segundos tras no ver enemigo para apagar torre.
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ATorre_Disparador::Idle);    
    Super::ProgramarTimer(Delegate, Espera, false);

}

void ATorre_Disparador::Idle() {
    RealizarAnimacion(1); // Desapuntar

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


void ATorre_Disparador::InicializacionAtaque() {
    

    // Inicializar estado de ataque, settear timer para que tras cooldown inicial se empiece a disparar

    RealizarAnimacion(2); // Apuntar
    this->RepetirCicloAtaque();
}


void ATorre_Disparador::RepetirCicloAtaque() {

    Super::ClearTimer();
    float Espera = this->TiempoParaAnimacionEnTiro;
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ATorre_Disparador::Atacar, true, 0);    
    Super::ProgramarTimer(Delegate, Espera, false);
    
}



void ATorre_Disparador::Atacar(bool FasePrepararTiro, int NumDisparo) {



    if (FasePrepararTiro) {
        
        // Estado 0: Animar carga de disparo

        Super::RealizarAnimacion(NumDisparo+3); // Animar el disparo
        

        // Settear la llmamada para disparar

        float Espera = this->TiempoEntreTiros - this->TiempoParaAnimacionEnTiro;
        FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ATorre_Disparador::Atacar, false, NumDisparo);    
        Super::ProgramarTimer(Delegate, Espera, false);


    } else {

        // Estado 1: Crear el proyectil

        this->Disparar();
        
        float Espera;
       
        // Si quedan tiros todavía, se debe repetir el ciclo de ataque de nuevo al estado 0

        if (NumDisparo != this->CadenciaDeDisparo - 1) {

            // Quedan tiros: settear la llmamada al método de vuelta

            Espera = this->TiempoParaAnimacionEnTiro;    
            FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ATorre_Disparador::Atacar, true, NumDisparo+1);    
            Super::ProgramarTimer(Delegate, Espera, false);


        } else {
        
            // No quedan tiros: esperar cooldown final para empezar el siguiente ciclo

            Espera = this->CooldownFinal;
            FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ATorre_Disparador::RepetirCicloAtaque);    
            Super::ProgramarTimer(Delegate, Espera, false);


        }



    } 


}

void ATorre_Disparador::Disparar() {

    // Hacer aparecer el proyectil en el spawnpoint de proyectiles. El proyectil en sí se mueve con su lógica en su código

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; // Forzar al proyectil a que aparezca (por si justo se pone la torre encima de un robot)
    AProyectil* Proyectil = AActor::GetWorld()->SpawnActor<AProyectil>(this->ClaseBlueprintProyectil, this->SpawnProyectiles->GetComponentLocation(), SpawnProyectiles->GetComponentRotation(),SpawnParams);

}
