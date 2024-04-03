// Fill out your copyright notice in the Description page of Project Settings.


#include "MandoDeJugador_EnMenu.h"
#include "Blueprint/UserWidget.h"



void AMandoDeJugador_EnMenu::BeginPlay() {

    Super::BeginPlay();
    bShowMouseCursor = true;

    this->HUD = CreateWidget(this, this->ClaseHUD);
    this->HUD->AddToViewport();

}