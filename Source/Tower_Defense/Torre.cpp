// Fill out your copyright notice in the Description page of Project Settings.


#include "Torre.h"
#include "Entidad.h"
#include "GameFramework/Actor.h"
#include "Casilla.h"

void ATorre::Matar() {
    
    UE_LOG(LogTemp, Warning, TEXT("ELIMINAR DE CASILLA"));
 
    Cast<ACasilla>(AActor::GetOwner())->LiberarCasilla(); // En el caso de las torres, deben dejar de ocupar la casilla


    AEntidad::Matar(); // Después, se puede destruir ya la torre del mundo

}


