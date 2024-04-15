// Fill out your copyright notice in the Description page of Project Settings.


#include "MandoDeJugador_EnMenu.h"
#include "Blueprint/UserWidget.h"



void AMandoDeJugador_EnMenu::BeginPlay() {

    Super::BeginPlay();
    bShowMouseCursor = true;



}


UUserWidget* AMandoDeJugador_EnMenu::CambiarAInterfaz(int ID) {


    TSubclassOf<class UUserWidget> ClaseUI = nullptr;

    switch (ID) {
        case 0:
            ClaseUI = ClaseHUDMenuPrincipal;
            break;
        case 1:
            ClaseUI = ClaseHUDMenuAjustes;

    }

    if (this->HUD) {
        this->HUD->RemoveFromViewport();
    }


    this->HUD = CreateWidget(this, ClaseUI);
    this->HUD->AddToViewport();

    return this->HUD;


}

