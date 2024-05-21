// Fill out your copyright notice in the Description page of Project Settings.


#include "MandoDeJugador_EnPartida.h"
#include "Casilla.h"
#include "Torre_Disparador.h"
#include "Blueprint/UserWidget.h"
#include "Torre_Producidor.h"
#include "Engine/Texture2D.h"
#include "GameMode_EnPartida.h"
#include "Engine/World.h"
#include "ConstructoraDeBlueprints.h"
#include "Guardador.h"
#include "Kismet/GameplayStatics.h"


void AMandoDeJugador_EnPartida::BeginPlay() {

    Super::BeginPlay();
    bShowMouseCursor = true;
    this->EnPartida = false;


    // Obtener de la save que torres desbloqueó el jugador

    UGuardador* Guardado = Cast<UGuardador>(UGameplayStatics::LoadGameFromSlot(TEXT("save"), 0));
    this->IDsTorresDesbloqueadas = Guardado->IDsTorresDesbloqueadas;


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





void AMandoDeJugador_EnPartida::Pinchar() {


    if (!this->EnPartida) {return;} // Si todavía se está en la selección de torres, ignorar cualquier tipo de click en el ambiente porque no importan clicks
                                    // que no sean a UIs

	FHitResult Resultado;
    APlayerController::GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel8, false , Resultado); 
    AActor* Target = Resultado.GetActor();   
    




    ACasilla* Casilla = Cast<ACasilla>(Target);

    if (Casilla) {


        if (Casilla->CasillaVacia()) { // Si la casilla está vacía...

            // La casilla esta vacia, asumimos que el player quiere poner una torre aqui

            int IDTorreElegida = this->ObtenerIDDeTorreElegidaEnPartida();
            int PosicionTorreEnUI = this->SeleccionDelJugador;
 
            if (IDTorreElegida != -1) { // Si había selección en UI
                Casilla->SpawnearTorre(IDTorreElegida); // Entonces poner la torre elegida en la casilla
                
                this->UsarSeleccionElegida();
                this->NotificarAInterfazColoqueTorre(PosicionTorreEnUI);
            }

        } else if (this->TNTElegida()) {  // Si la TNT está elegida..

            Casilla->DestruirTorre(); // Si lo está, quitamos la torre de la casilla elegida (si había, si no, no hace nada)

            this->UsarSeleccionElegida();
            this->NotificarAInterfazUsoTNT();

        } else { // Si no se tiene la TNT elegida, comprobar si la casilla pinchada aloja un producidor

                ATorre_Producidor* TorreProducidor = Cast<ATorre_Producidor>(Casilla->ObtenerTorreEnCasilla());

                if (TorreProducidor) {
                    // Si lo hace, tratar de recolectar su energia
                    TorreProducidor->Click();
                }
        }

        
    } else {

        // Si no es una casilla, comprobar si es un producidor de energia (requieren ser pinchados para recolectar energia)

        ATorre_Producidor* Torre = Cast<ATorre_Producidor>(Target);

        if (Torre) {

            // Si lo es, ver si tenemos la TNT seleccionada
            
            if (this->TNTElegida()) {

                // Pala seleccionada, vamos a su casilla para borrar la Torre (si no tiene casilla relacionada como el panel por defecto, entonces no hace nada)

                ACasilla* CasillaDeTorre = Cast<ACasilla>(Torre->GetOwner());

                if (CasillaDeTorre) {

                    this->UsarSeleccionElegida();
                    this->NotificarAInterfazUsoTNT();

                    CasillaDeTorre->DestruirTorre();
                }


            } else {

                // Pala no seleccionada, recolectar energia en su lugar

                Torre->Click();
            }
        }





    }

  
    

    

}

void AMandoDeJugador_EnPartida::ObtenerTodasLasImagenesYCostesDeTorre(TArray<UTexture2D*>& Imagenes, TArray<int>& Costes) const {
    Imagenes = this->ObtenerImagenesDeTorres(this->IDsTorresDesbloqueadas);
    Costes = this->ObtenerCostesDeTorres(this->IDsTorresDesbloqueadas);
}



TArray<UTexture2D*> AMandoDeJugador_EnPartida::ObtenerImagenesDeTorres(TArray<int> IDs) const {
    


    ConstructoraDeBlueprints* CdB = ConstructoraDeBlueprints::GetConstructoraDeBlueprints();
    TArray<UTexture2D*> Texturas;

    for (int ID : IDs) {
        Texturas.Add(CdB->ObtenerImagenDeTorre(ID));
    }

    return Texturas;
}



TArray<int> AMandoDeJugador_EnPartida::ObtenerCostesDeTorres(TArray<int> IDs) const {

    ConstructoraDeBlueprints* CdB = ConstructoraDeBlueprints::GetConstructoraDeBlueprints();
    TArray<int> Costes;

    for (int ID : IDs) {
        Costes.Add(CdB->GetCosteDeTorre(ID));
    }

    return Costes;
}

TArray<float> AMandoDeJugador_EnPartida::ObtenerRecargasDeTorres(TArray<int> IDs) const {

    TArray<float> ListaRecargas;

    for (int ID : IDs) {
        ListaRecargas.Add(ConstructoraDeBlueprints::GetConstructoraDeBlueprints()->GetTiempoDeRecargaDeTorre(ID));
    }
    return ListaRecargas;


}

TArray<bool> AMandoDeJugador_EnPartida::ObtenerEmpiezaRecargadosTorres(TArray<int> IDs) const {
        
    TArray<bool> ListaRecargaEmpezada;

    for (int ID : IDs) {
        ListaRecargaEmpezada.Add(ConstructoraDeBlueprints::GetConstructoraDeBlueprints()->GetEmpiezaRecargadaTorre(ID));
    }
    return ListaRecargaEmpezada;
}	







int AMandoDeJugador_EnPartida::SlotDeTorreDesbloqueadaEnPosDeSeleccion(int Slot) {

    // Post: Busca si la torre número slot desbloqueada en la save está añadida ya en la seleccion de torres del jugador. Returns la posicion si true, -1 si no está
    
    int ID = this->IDsTorresDesbloqueadas[Slot];

    for (int Pos = 0; Pos != this->IDsDeTorresElegidas.Num(); Pos++) {
        if (this->IDsDeTorresElegidas[Pos] == ID) {
            return Pos;
        }
    }

    return -1;
}

void AMandoDeJugador_EnPartida::ProcesarClickEnSeleccionInicialDeTorres(int Slot, int& PosAccion, bool& PermiteEmpezar) {

    // Post: PosAccion: (0-5) index que se ha quitado, (-1) se ha insertado, (-2) no accion
    //       PermiteEmpezar: Todas las torres seleccionadas desbloqueadas o al menos hay 6 elegidas

    int PosSeleccion = this->SlotDeTorreDesbloqueadaEnPosDeSeleccion(Slot); // Comprobar si la torre está elegida

    if (PosSeleccion == -1) {

        // No está elegida, comprobar si se puede añadir (hay 6 huecos en el layout, ver si no hay 6 torres elegidas)


        if (this->IDsDeTorresElegidas.Num() != 6) {
            
            // Hay hueco, insertar la torre al final de la lista 

            PosAccion = -1;

            this->IDsDeTorresElegidas.Add(this->IDsTorresDesbloqueadas[Slot]);

            // Se permite empezar si hay 6 torres elegidas o todas las desbloqueadas están elegidas

            PermiteEmpezar = this->IDsDeTorresElegidas.Num() == 6 || this->IDsDeTorresElegidas.Num() == this->IDsTorresDesbloqueadas.Num();

        } else {

            // No hay hueco, el usuario ya tiene 6 torres elegidas.

             PosAccion = -2;

            PermiteEmpezar = true;
        }



    } else {
        // Está elegida, proceder a quitarla de la lista. Se informa a la UI también de la posición de la lista con PosSeleccion a quitar visualmente
        
        PosAccion = PosSeleccion;


        this->IDsDeTorresElegidas.RemoveAt(PosSeleccion); // Usar borrado más lento shifteando las posiciones del array hacia adelante para que encaje visualmente con la UI

        // Tras quitar una torre debe haber al menos un espacio libre, por lo que no se permite empezar
        PermiteEmpezar = false;


    }

}





TArray<int> AMandoDeJugador_EnPartida::GetTorresElegidas() const {


    return this->IDsDeTorresElegidas;
}


void AMandoDeJugador_EnPartida::InicializarVariablesDePartida() {

    ConstructoraDeBlueprints* CdB = ConstructoraDeBlueprints::GetConstructoraDeBlueprints();
    UWorld* Mundo = GetWorld();
    
    for (int ID : this->IDsDeTorresElegidas) {
        int TiempoDeRecarga = CdB->GetTiempoDeRecargaDeTorre(ID);

        this->TiempoDeRecargaDeTorres.Add(TiempoDeRecarga);
        this->CosteDeTorres.Add(CdB->GetCosteDeTorre(ID));


        if (ConstructoraDeBlueprints::GetConstructoraDeBlueprints()->GetEmpiezaRecargadaTorre(ID)) {
            this->MomentoEnQueTorreRecarga.Add(Mundo->GetTimeSeconds());

        } else {
            this->MomentoEnQueTorreRecarga.Add(TiempoDeRecarga + Mundo->GetTimeSeconds());

        }


    }

 
	this->SeleccionDelJugador = -1;
	this->Energia = 20;
    this->EnPartida = true;


}



void AMandoDeJugador_EnPartida::ElegirTorre(int PosTorre, bool& SeleccionCorrecta, int& SeleccionPrevia, bool& SeleccionPreviaCorrecta) {

    // Pre: Pos indica una torre

    if (this->SeleccionDelJugador > 6) {
        SeleccionPrevia = this->SeleccionDelJugador - 7;
        SeleccionPreviaCorrecta = false;
    } else {
        SeleccionPrevia = this->SeleccionDelJugador;
        SeleccionPreviaCorrecta = true;
    }

    
    UE_LOG(LogTemp, Warning, TEXT("Coste: %d"), this->CosteDeTorres[PosTorre]);
    UE_LOG(LogTemp, Warning, TEXT("Momento actual: %f | Momento de recarga: %f"), GetWorld()->GetTimeSeconds(), this->MomentoEnQueTorreRecarga[PosTorre]);



    if (this->Energia >= this->CosteDeTorres[PosTorre] && GetWorld()->GetTimeSeconds() >= this->MomentoEnQueTorreRecarga[PosTorre]) {

        if (this->SeleccionDelJugador == PosTorre) {
            this->SeleccionDelJugador = -1;
        } else {
            this->SeleccionDelJugador = PosTorre;

        }



        SeleccionCorrecta = true;
    } else {
        this->SeleccionDelJugador = PosTorre+7;

        SeleccionCorrecta = false;   
    }

}


void AMandoDeJugador_EnPartida::ElegirTNT(int& SeleccionPrevia, bool& TntElegida) {
    

    if (this->SeleccionDelJugador > 6) {
        SeleccionPrevia = this->SeleccionDelJugador - 7;
    } else {
        SeleccionPrevia = this->SeleccionDelJugador;
    }

    if (this->SeleccionDelJugador != 6) {
        this->SeleccionDelJugador = 6;
        TntElegida = true;

    } else {
        this->SeleccionDelJugador = -1;
        TntElegida = false;

    }

}



void AMandoDeJugador_EnPartida::ObtenerUltimaSeleccionTorre(int& Seleccion, bool& Correcto) const {
    
    if (this->SeleccionDelJugador > 6) {
        Seleccion = this->SeleccionDelJugador - 7;
        Correcto = false;
    } else {
        Seleccion = this->SeleccionDelJugador;
        Correcto = true;
    }

}
void AMandoDeJugador_EnPartida::ActualizarEnergiaPor(int Surplus) {
    this->Energia = this->Energia + Surplus;
    this->NotificarAInterfazCambioEnDinero(this->Energia);

}

void AMandoDeJugador_EnPartida::UsarSeleccionElegida() {
    if (this->SeleccionDelJugador != -1 && this->SeleccionDelJugador < 6) {
        this->ActualizarEnergiaPor(-this->CosteDeTorres[this->SeleccionDelJugador]);
        this->MomentoEnQueTorreRecarga[SeleccionDelJugador] = GetWorld()->GetTimeSeconds() + this->TiempoDeRecargaDeTorres[this->SeleccionDelJugador];
    }

    this->SeleccionDelJugador = -1;

}


int AMandoDeJugador_EnPartida::ObtenerCantidadEnergia() const {
    return this->Energia;
}

bool AMandoDeJugador_EnPartida::TNTElegida() {
    return  this->SeleccionDelJugador == 6;

}

int AMandoDeJugador_EnPartida::ObtenerIDDeTorreElegidaEnPartida() {
    
    if (this->SeleccionDelJugador >= 0 && this->SeleccionDelJugador < 6) {
        return this->IDsDeTorresElegidas[this->SeleccionDelJugador];

    } else {
        return -1;

    }
}
