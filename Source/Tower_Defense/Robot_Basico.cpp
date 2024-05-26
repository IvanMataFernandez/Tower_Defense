// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot_Basico.h"
#include "Math/UnrealMathUtility.h"
#include "Proyectil.h"
#include "MandoDeIA.h"
#include "Robot.h"
#include "Components/BoxComponent.h"


// Todo robot que se puede mover y disparar forma parte de Robot_Basico

/*

    IDs de animaciones:
   -2: Mostrar estado 2 vida (dañado)
   -1: Mostrar estado 1 vida  (muy dañado)
    0: Morir
    1: Moverse
    2: Parar de moverse
    3: Disparar laser

*/

ARobot_Basico::ARobot_Basico() {

    // Settear componentes exclusivos como el spawneador de proyectiles que su clase padre no implementa

    this->MeshDisparador = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshDisparador"));
    this->SpawnProyectiles = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnProyectiles"));

    this->MeshDisparador->SetupAttachment(RootComponent);
    this->SpawnProyectiles->SetupAttachment(this->MeshDisparador);

}


void ARobot_Basico::BeginPlay() {
    Super::BeginPlay();
    this->DistanciaAObjetivo = -1.f;
}

void ARobot_Basico::InicializarMover() {



    Super::InicializarMover(); // Empieza a mover el robot usando el codigo de la clase Robot

    // Checkear si tiene alguien detras encolado para darle instrucciones

    if (ARobot_Basico* Subordinado = Cast<ARobot_Basico>(Super::GetLideraA())) {

        Subordinado->DistanciaAObjetivo = -1.f;
	    Subordinado->GetMandoDeIA()->SettearBoolEnBlackboard(TEXT("TorreEnRango"), false);

    }
    // Si se fueran a crear robots que no atacan (que solo hereden de robot, habría que implementar lógica aquí que handlee este tipo de robots)
}



void ARobot_Basico::Parar() {

    Super::Parar(); // Instruciones de parar el robot en sí (Esta instancia)


    // Comprobar cola 

    if (ARobot_Basico* Subordinado = Cast<ARobot_Basico>(Super::GetLideraA())) {
        // Si tiene alguien por detrás en la cola que también puede disparar (todos los robots pueden disparar en esta version), decirle que se pare también

        Subordinado->DistanciaAObjetivo = this->DistanciaAObjetivo + Subordinado->Hitbox->GetScaledBoxExtent().Y * 2;
	    Subordinado->GetMandoDeIA()->SettearBoolEnBlackboard(TEXT("TorreEnRango"), true);

        // Decirle la distancia que tiene hasta dicho target (es la distancia del robot actual al target + la hitbox del robot de atrás, se llama recursivamente por toda la cola)

    }
    // Si se fueran a crear robots que no atacan (que solo hereden de robot, habría que implementar lógica aquí que handlee este tipo de robots)

}


void ARobot_Basico::DarInfoDeColaASubordinado(ARobot* Subordinado) {

    Super::DarInfoDeColaASubordinado(Subordinado);

    if  (ARobot_Basico* SubordinadoDisparador = Cast<ARobot_Basico> (Subordinado)) {

        if (this->DistanciaAObjetivo > -0.5f) {
            SubordinadoDisparador->DistanciaAObjetivo = this->DistanciaAObjetivo + SubordinadoDisparador->Hitbox->GetScaledBoxExtent().Y * 2;

	        SubordinadoDisparador->GetMandoDeIA()->SettearBoolEnBlackboard(TEXT("TorreEnRango"), true);

        } else {
            SubordinadoDisparador->DistanciaAObjetivo =  -1.f;
	        SubordinadoDisparador->GetMandoDeIA()->SettearBoolEnBlackboard(TEXT("TorreEnRango"), false);

        }

    }



}


// Métodos del árbol de IA:

bool ARobot_Basico::TorreEnRango() {


    if (!Super::EsLider()) {

        // Si no es lider, el lider le dice si debe disparar o no, para ello comprobar si está setteada la variable de distancia al target
        // El lider se encarga de pasar este valor por toda la cola cuando decide targettear / dejar de targettear.

        return this->DistanciaAObjetivo > -0.5f;
    }

    // Siendo el lider de la cola, decidir si debe atacar o no.


    FVector Start =  this->SpawnProyectiles->GetComponentLocation();
    FVector End = Start - (FVector(0,256.f+this->RangoEnCasillas*512.f,0) ); // Cada casilla son 512.f. 256.f para offsettear la casilla sobre la que está.

    // Realiza el line trace y devuelve si hay hit de torre en rango
    FHitResult HitResult;


    if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_GameTraceChannel6)) {
        // Hay hit en linetrace

        if (this->DistanciaAObjetivo < -0.1f) {
            // Se acaba de encontrar un target, calcular la distancia a él
            this->DistanciaAObjetivo = this->GetActorLocation().Y - HitResult.GetActor()->GetActorLocation().Y;

        }

        return true;


    } else {
        // No hay hit en linetrace

        if (this->DistanciaAObjetivo > -0.1f) {
            // Se acaba de perder el target, borrar la distancia a objetivo guardada
            this->DistanciaAObjetivo = -1.f;

        }

        return false;
    }


}


void ARobot_Basico::AnimarDisparo() {
    
    Super::RealizarAnimacion(3); // Animar el robot para que realize el disparo

    Super::ProgramarTimerFinDeTareaIA(this->TiempoDeAnimacionDisparo);

}

void ARobot_Basico::Disparar() {

    // Generar el disparo

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; // Forzar al proyectil a que aparezca (por si justo se le pone una torre encima)
    AProyectil* Proyectil = AActor::GetWorld()->SpawnActor<AProyectil>(this->ClaseBlueprintProyectil, this->SpawnProyectiles->GetComponentLocation(), SpawnProyectiles->GetComponentRotation(),SpawnParams);
    

    // Settear la velocidad de caída basado en la distancia entre el robot y su target

    if (Proyectil) { // Check si el proyectil existe (Si spawnea encima de un bot se quita y aplica el daño instantaneamente, omitiendo así este paso)
        Proyectil->SetVelocidadDeCaida(SpawnProyectiles->GetRelativeLocation().Z , this->DistanciaAObjetivo);

    }

    
    
    Super::ProgramarTimerFinDeTareaIA(this->TiempoDeDisparo);

}

