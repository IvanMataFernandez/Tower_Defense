// Fill out your copyright notice in the Description page of Project Settings.


#include "MandoDeJugador_EnMenu.h"
#include "Blueprint/UserWidget.h"



// El mando de jugador usado en el menú principal. Lo único que hace es cambiar de interfaz si se le da la orden de hacerlo
// (generalmente tras pinchar en un botón de una interfaz)


void AMandoDeJugador_EnMenu::BeginPlay() {

    Super::BeginPlay();
    bShowMouseCursor = true;



}


UUserWidget* AMandoDeJugador_EnMenu::CambiarAInterfaz(int ID) {


    // Cargar la interfaz adecuada según el ID indicado, se quita la anterior

    TSubclassOf<class UUserWidget> ClaseUI = nullptr;

    switch (ID) {
        case 0:
            ClaseUI = ClaseHUDMenuPrincipal;
            break;
        case 1:
            ClaseUI = ClaseHUDMenuTutorial;
            break;
        case 2:
            ClaseUI = ClaseHUDMenuAjustes;
            break;

        case 3:
            ClaseUI = ClaseHUDPopUpJuegoCompleto;
            break;
        case 4:
            ClaseUI = ClaseHUDAvisoJuegoNuevo;
            break;
    }

    if (this->HUD) { // Quitar la interfaz anterior
        this->HUD->RemoveFromViewport();
    }

    // Cargar la nueva interfaz

    this->HUD = CreateWidget(this, ClaseUI);
    this->HUD->AddToViewport();

    return this->HUD;


}

