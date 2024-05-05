// Fill out your copyright notice in the Description page of Project Settings.


#include "MandoDeJugador_EnPartida.h"
#include "Casilla.h"
#include "Torre_Disparador.h"
#include "Blueprint/UserWidget.h"
#include "Torre_Producidor.h"
#include "Engine/Texture2D.h"



void AMandoDeJugador_EnPartida::BeginPlay() {

    Super::BeginPlay();
    bShowMouseCursor = true;


}


void AMandoDeJugador_EnPartida::Pausar() {
    this->SetPause(true);
}   

void AMandoDeJugador_EnPartida::PausarEn(float Segundos) {
    FTimerHandle TimerParaPausa;
    GetWorld()->GetTimerManager().SetTimer(TimerParaPausa, this, &AMandoDeJugador_EnPartida::Pausar,Segundos, false);               

}

UUserWidget* AMandoDeJugador_EnPartida::CrearHUD(int Seleccion) {

    UUserWidget* HUD;
    if (Seleccion == 0) {
        HUD = CreateWidget(this, this->ClaseHUDElegirTorre);
    } else if (Seleccion == 1) {
        HUD = CreateWidget(this, this->ClaseHUDCuentaAtras);

    } else if (Seleccion == 2) {
        HUD = CreateWidget(this, this->ClaseHUDEnPartida);
    } else if (Seleccion == 3) {
        HUD = CreateWidget(this, this->ClaseHUDDerrota);

    } else if (Seleccion == 4) {
        HUD = CreateWidget(this, this->ClaseHUDVictoria);

    } else {
        HUD = CreateWidget(this, this->ClaseHUDPausa);
        
    }

    HUD->AddToViewport();
    this->HUDs.Add(HUD);

    return HUD;

}



UUserWidget* AMandoDeJugador_EnPartida::ObtenerHUD(int Pos) const {

    if (Pos >= 0 && Pos < this->HUDs.Num()) {
        return this->HUDs[Pos];

    } else {
        return nullptr;
    }


}




void AMandoDeJugador_EnPartida::QuitarUltimaHUDAnadida()  {
    this->QuitarHUD(this->HUDs.Num()-1);
}

void AMandoDeJugador_EnPartida::QuitarHUD(int Pos)  {
    if (Pos >= 0 && Pos < this->HUDs.Num()) {
        this->HUDs[Pos]->RemoveFromParent();
        this->HUDs.RemoveAt(Pos);
    } else {
        UE_LOG(LogTemp, Error, TEXT("Se habria producido crash"));
    }



}


void AMandoDeJugador_EnPartida::SetTorresElegidas(TArray<int> IDs) {
    this->IDTorresElegidas = IDs;
}

TArray<int> AMandoDeJugador_EnPartida::GetTorresElegidas() const {
    return this->IDTorresElegidas;
}



void AMandoDeJugador_EnPartida::Pinchar() {
	FHitResult Resultado;
    APlayerController::GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel8, false , Resultado); 
    AActor* Target = Resultado.GetActor();   
   



    ACasilla* Casilla = Cast<ACasilla>(Target);

    if (Casilla) {


        if (Casilla->CasillaVacia()) {

            // La casilla esta vacia, asumimos que el player quiere poner una torre aqui

            this->SettearSeleccionDeTorre(); // Recoger el ID desde la UI
            
            if (this->SeleccionDeTorre != -1) { // Si había selección en UI de Torre Correcta.
                Casilla->SpawnearTorre(this->SeleccionDeTorre); // Entonces poner la torre elegida en la casilla
            }

        } else {

            // Comprobar si la TNT está seleccionado
            this->SettearBorradorDeTorre();

            if (this->SeleccionDeTorre == 1) { 


                Casilla->DestruirTorre(); // Si lo está, quitamos la torre del nivel

            } else {

                // Si no se tiene la TNT elegida, comprobar si la casilla pinchada aloja un producidor

                ATorre_Producidor* TorreProducidor = Cast<ATorre_Producidor>(Casilla->ObtenerTorreEnCasilla());

                if (TorreProducidor) {
                    // Si lo hace, tratar de recolectar su energia
                    TorreProducidor->Click();
                }

                
            }
        }

    } else {

        // Si no es una casilla, comprobar si es un producidor de energia (requieren ser pinchados para recolectar energia)

        ATorre_Producidor* Torre = Cast<ATorre_Producidor>(Target);

        if (Torre) {

            // Si lo es, ver si tenemos la TNT seleccionada
            this->SettearBorradorDeTorre();
            
            if (this->SeleccionDeTorre == 1) {

                // Pala seleccionada, vamos a su casilla para borrar la Torre (si no tiene casilla relacionada como el panel por defecto, entonces no hace nada)

                ACasilla* CasillaDeTorre = Cast<ACasilla>(Torre->GetOwner());

                if (CasillaDeTorre) {
                    CasillaDeTorre->DestruirTorre();
                }


            } else {

                // Pala no seleccionada, recolectar energia en su lugar

                Torre->Click();
            }
        }





    }

  
    

    

}

