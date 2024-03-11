// Fill out your copyright notice in the Description page of Project Settings.


#include "Torre.h"
#include "Entidad.h"
#include "GameFramework/Actor.h"

void ATorre::Matar() {

    AActor::SetOwner(nullptr); // EN el caso de la torres, se deben desvincular de las casillas.

    AEntidad::Matar(); // Después, se puede destruir ya la torre del mundo

}


