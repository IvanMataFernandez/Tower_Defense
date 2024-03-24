// Fill out your copyright notice in the Description page of Project Settings.


#include "MandoDeJugador_EnPartida.h"
#include "Casilla.h"
#include "Torre_Disparador.h"
#include "ConstructoraDeBlueprints.h"
#include "Blueprint/UserWidget.h"
#include "Torre_Producidor.h"
#include "Engine/Texture2D.h"



void AMandoDeJugador_EnPartida::BeginPlay() {
    Super::BeginPlay();
    bShowMouseCursor = true;

    this->HUD = CreateWidget(this, this->ClaseHUD);
    this->HUD->AddToViewport();

}


TArray<int> AMandoDeJugador_EnPartida::ObtenerCostesDeTorres(TArray<int> IDs) {

    TArray<int> ListaCostes;

    for (int ID : IDs) {
        ListaCostes.Add(ConstructoraDeBlueprints::GetConstructoraDeBlueprints()->GetCosteDeTorre(ID));
    }
    return ListaCostes;
    
}
TArray<float> AMandoDeJugador_EnPartida::ObtenerRecargasDeTorres(TArray<int> IDs) {

    TArray<float> ListaRecargas;

    for (int ID : IDs) {
        ListaRecargas.Add(ConstructoraDeBlueprints::GetConstructoraDeBlueprints()->GetTiempoDeRecargaDeTorre(ID));
    }
    return ListaRecargas;


}

TArray<bool> AMandoDeJugador_EnPartida::ObtenerEmpiezaRecargadosTorres(TArray<int> IDs) {
        
    TArray<bool> ListaRecargaEmpezada;

    for (int ID : IDs) {
        ListaRecargaEmpezada.Add(ConstructoraDeBlueprints::GetConstructoraDeBlueprints()->GetEmpiezaRecargadaTorre(ID));
    }
    return ListaRecargaEmpezada;
}	


TArray<UTexture2D*> AMandoDeJugador_EnPartida::ObtenerImagenesDeTorres(TArray<int> IDs) {
    
    TArray<UTexture2D*> ListaTexturas;

    for (int ID : IDs) { 
        FString Ruta = TEXT("/Game/Assets/Texturas/Torre") + FString::Printf(TEXT("%d"), ID);
        UTexture2D* Textura = LoadObject<UTexture2D>(nullptr, *Ruta);

        ListaTexturas.Add(Textura);
    }
    return ListaTexturas;
}




void AMandoDeJugador_EnPartida::Pinchar() {
	FHitResult Resultado;
    APlayerController::GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel8, false , Resultado); 
    AActor* Target = Resultado.GetActor();   
   
    ACasilla* Casilla = Cast<ACasilla>(Target);


    if (Casilla && Casilla->CasillaVacia()) { // Comprobar si la casilla pinchada está vacía
        this->SettearSeleccionDeTorre(); // Recoger el ID desde la UI
        if (SeleccionDeTorre != -1) { // Si había selección en UI
            Casilla->SpawnearTorre(this->SeleccionDeTorre); // Entonces poner la torre elegida en la casilla
        }
    
    } else {

        // Si se pincha en una torre producidora, tratar de colectar su energia

        ATorre_Producidor* Torre = Cast<ATorre_Producidor>(Target);

        if (Torre) {
            Torre->Click();
        }

    }


    

}