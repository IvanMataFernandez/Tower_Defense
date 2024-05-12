

// Fill out your copyright notice in the Description page of Project Settings.


#include "Musica_EnPartida.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "Guardador.h"
#include "Kismet/GameplayStatics.h"



void AMusica_EnPartida::BeginPlay() {
    Super::BeginPlay();
    this->Parar();
}

void AMusica_EnPartida::Tocar(int ID) {
    this->Parar();
    USoundBase* MusicaATocar = nullptr;

    switch (ID) {
        case 0:
            MusicaATocar = this->MusicaInicio;
            break;
        case 1:
           MusicaATocar = this->MusicaMedio;
            break;
        case 2:
            MusicaATocar = this->MusicaFin;
            break;
        case 3:
            MusicaATocar = this->MusicaSeleccionDeTorres;
            break;
        case 4:
            MusicaATocar = this->MusicaCuentaAtras;
            break;
        case 5:
            MusicaATocar = this->MusicaRobotLlegaATarget;
            break;
        case 6:
            MusicaATocar = this->MusicaDerrota;
            break;
        case 7:
            MusicaATocar = this->MusicaVictoria;

    } 
    UGuardador* Guardador = Cast<UGuardador>(UGameplayStatics::LoadGameFromSlot(TEXT("save"), 0));

    this->GetAudioComponent()->VolumeMultiplier = Guardador->VolumenAudio;



    this->GetAudioComponent()->SetSound(MusicaATocar);
    this->GetAudioComponent()->Play(0.f);
    
}
void AMusica_EnPartida::Parar() {
    this->GetAudioComponent()->Stop();
    this->Stop();
}
