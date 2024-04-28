// Fill out your copyright notice in the Description page of Project Settings.


#include "Torre_Disparador.h"
#include "Components/SceneComponent.h"
#include "Proyectil.h"
#include "TimerManager.h"

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
    float Espera = 1.5f; // Esperar 1,5 segundos tras no ver enemigo para apagar torre.
    GetWorld()->GetTimerManager().SetTimer(TimerFrame, this, &ATorre_Disparador::Idle, Espera, false);               

}

void ATorre_Disparador::Idle() {
    RealizarAnimacion(1); // Desapuntar

}


bool ATorre_Disparador::EnRango() {
    
    // Realiza el line trace y devuelve si hay hit.

    FVector Start =  this->SpawnProyectiles->GetComponentLocation();
    FVector End = Start + (FVector(0,256.f+this->RangoEnCasillas*512.f,0) ); //Cada casilla son 512.f. 256.f para offsettear la casilla sobre la que está

    FHitResult HitResult;
 //   DrawDebugLine(GetWorld(), Start, End, FColor::Green, true);


    return GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_GameTraceChannel5); // 5 vision torre, 6 vision robot



}


void ATorre_Disparador::InicializacionAtaque() {
    

    // Inicializar estado de ataque, settear timer para que tras cooldown inicial se empiece a disparar

    RealizarAnimacion(2); // Apuntar
    this->RepetirCicloAtaque();
}


void ATorre_Disparador::RepetirCicloAtaque() {

    Super::ClearTimer();
    float Espera = this->TiempoParaAnimacionEnTiro;
    this->TirosRestantes = this->CadenciaDeDisparo; 
    this->TocaAnimar = true;
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ATorre_Disparador::Atacar, Espera);
    GetWorld()->GetTimerManager().SetTimer(TimerFrame, Delegate, Espera, false);
    Timer = 0.f;
}



void ATorre_Disparador::Atacar(float DeltaTime) {

    Timer = Timer + DeltaTime;


    if (this->TocaAnimar) {

        RealizarAnimacion((this->CadenciaDeDisparo-this->TirosRestantes)+3); // Animar el disparo
        this->TocaAnimar = false;
        
        // Settear la llmamada para disparar

        float Espera = this->TiempoEntreTiros - this->TiempoParaAnimacionEnTiro;

        FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ATorre_Disparador::Atacar, Espera);
        GetWorld()->GetTimerManager().SetTimer(TimerFrame, Delegate, Espera, false);   

    } else {
        // Si quedan tiros todavía, se debe disparar

        float Espera;

        this->Disparar();

        if (this->TirosRestantes != 0) {
            Espera = this->TiempoParaAnimacionEnTiro;
            this->TocaAnimar = true;
                    
            // Settear la llmamada al método de vuelta
            FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ATorre_Disparador::Atacar, Espera);
            GetWorld()->GetTimerManager().SetTimer(TimerFrame, Delegate, Espera, false);
        
        } else {
        
            // Si no quedaban tiros, esperar cooldown final para empezar el siguiente ciclo


            Espera = this->CooldownFinal;

            GetWorld()->GetTimerManager().SetTimer(TimerFrame, this, &ATorre_Disparador::RepetirCicloAtaque,Espera, false);               
        }



    } 


}

void ATorre_Disparador::Disparar() {

    // Hacer aparecer el proyectil en el spawnpoint de proyectiles. El proyectil en sí se mueve con su lógica en su código

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; // Forzar al proyectil a que aparezca (por si justo se pone la torre encima de un robot)
    AProyectil* Proyectil = AActor::GetWorld()->SpawnActor<AProyectil>(this->ClaseBlueprintProyectil, this->SpawnProyectiles->GetComponentLocation(), SpawnProyectiles->GetComponentRotation(),SpawnParams);
    this->TirosRestantes--;
}
