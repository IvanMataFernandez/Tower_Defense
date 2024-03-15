// Fill out your copyright notice in the Description page of Project Settings.


#include "Torre.h"
#include "Entidad.h"
#include "GameFramework/Actor.h"
#include "Casilla.h"

void ATorre::Matar() {
    
    UE_LOG(LogTemp, Warning, TEXT("ELIMINAR DE CASILLA"));
 

    // TODO: Cambiar esto en producto final. Esto es un workaround para que no crashee el programa con torres colocadas encima de casillas en el motor de juego sin pinchar en ellas

    ACasilla* Casilla = Cast<ACasilla>(AActor::GetOwner());

    // En el caso de las torres, deben dejar de ocupar la casilla

    if (Casilla) {
        Casilla->LiberarCasilla();
    }



    AEntidad::Matar(); // Después, se puede destruir ya la torre del mundo

}


