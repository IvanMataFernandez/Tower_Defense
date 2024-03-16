// Fill out your copyright notice in the Description page of Project Settings.


#include "Torre_Disparador.h"
#include "Components/SceneComponent.h"
#include "Proyectil.h"
#include "TimerManager.h"

#include "DrawDebugHelpers.h"


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

    // TODO: Empezar Idle
}

bool ATorre_Disparador::EnRango() {

    FVector Start =  this->SpawnProyectiles->GetComponentLocation();
    FVector End = Start + (FVector(0,256.f+this->RangoEnCasillas*512.f,0) ); //Cada casilla son 512.f. 256.f para offsettear la casilla sobre la que está

    // Realiza el line trace y devuelve si hay hit.
    FHitResult HitResult;
 //   DrawDebugLine(GetWorld(), Start, End, FColor::Green, true);



    return GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_GameTraceChannel5); // 5 vision torre, 6 vision robot



}


void ATorre_Disparador::InicializacionAtaque() {
    

    // Inicializar estado de ataque, settear timer para que tras cooldown inicial se empiece a disparar

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
        // Empezar a animar el disparo

        RealizarAnimacion((this->CadenciaDeDisparo-this->TirosRestantes)+1);
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

            GetWorld()->GetTimerManager().SetTimer(TimerFrame, this, &ATorre_Disparador::InicializacionAtaque,Espera, false);               
        }



    } 


}

void ATorre_Disparador::Disparar() {

    // Hacer aparecer el proyectil en el spawnpoint de proyectiles. El proyectil en sí se mueve con su lógica en su código


    AProyectil* Proyectil = AActor::GetWorld()->SpawnActor<AProyectil>(this->ClaseBlueprintProyectil, this->SpawnProyectiles->GetComponentLocation(), SpawnProyectiles->GetComponentRotation());
    this->TirosRestantes--;
}
