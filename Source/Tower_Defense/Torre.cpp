// Fill out your copyright notice in the Description page of Project Settings.


#include "Torre.h"
#include "Entidad.h"
#include "GameFramework/Actor.h"
#include "Casilla.h"
#include "MandoDeIA.h"


void ATorre::Matar() {
    
    // Si la torre muere a robot...


    ACasilla* Casilla = Cast<ACasilla>(AActor::GetOwner());

    // En el caso de las torres, deben dejar de ocupar la casilla

    if (Casilla) {   // TODO: Cambiar esto en producto final. Esto es un workaround para que no crashee el programa con torres colocadas encima de casillas en el motor de juego sin pinchar en ellas (Lo mismo en quitar torre)
        Casilla->LiberarCasilla();
    }



    AEntidad::Matar(); // Después, se puede destruir ya la torre del mundo

}

void ATorre::QuitarTorre() {

    // Si el jugador quita la torre para hacer espacio...


    // Desactivar IA



    // Quitar de la casilla la torre


    
    ACasilla* Casilla = Cast<ACasilla>(AActor::GetOwner());

    if (Casilla) {  
        UE_LOG(LogTemp, Warning, TEXT("Liberar"));
 
        Casilla->LiberarCasilla();
    } else {
        UE_LOG(LogTemp, Warning, TEXT("NO Liberar"));

    } 
    /*

    AMandoDeIA* IA = Cast<AMandoDeIA>(this->GetController());

	if (IA) {
		this->DetachFromControllerPendingDestroy();
		IA->Destroy();
	}
    */


    // TODO: Considerar dar rembolso / sonido de quitar torre con "Pala"
    UE_LOG(LogTemp, Warning, TEXT("Destruir"));

    AActor::Destroy();

}


