// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot.h"
#include "Math/UnrealMathUtility.h"
#include "Proyectil.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "MandoDeIA.h"
#include "ComponenteVida.h"


// Todo robot implementa esta clase (los robots son móviles)

/*

    IDs de animaciones:
    0: Morir
    1: Mover ruedas (activar loop) 
    2: Mover ruedas (quitar loop) 


*/
ARobot::ARobot() {

    this->MeshDesplazador = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshDesplazador"));


    this->MeshDesplazador->SetupAttachment(PosicionBase);

}



void ARobot::BeginPlay() {
    Super::BeginPlay();

    // Tan pronto como spawnea rollear rng para ver que velocidad tiene (robots de mismo tipo incluyen ligera desviación de velocidad)

    this->VelocidadDeInstancia = this->VelocidadBase + (FMath::FRand() - 0.5) * 2 * this->DesviacionMaxVelocidad;
    this->DistanciaRecorridaVertical = 0;

    // Programar el evento de choque con otros robots para que se puedan encolar si es el caso
    Hitbox->OnComponentBeginOverlap.AddDynamic(this, &ARobot::EnChoque);

}

void ARobot::DeshacerEnlaceDeCola(bool Lider) {

    // Deshace el enlace de la cola con el bot de delante (true) o con el de atrás (false). Este método se llama cuando dicho otro robot va a morir

    if (Lider) {

        // Settear su lider a null

        if (this->LideradoPor) {
            this->LideradoPor = nullptr;
        }




        if (this->LideraA) {

            // Si lidera a alguien, ahora esta instancia es el lider global y la cola entera se settea a su speed original

            this->SetVelocidadDeCola(this->VelocidadDeInstancia);

        } else {

            // Si no lidera a nadie, se anula la velocidad de cola y se aplica la velocidadDeInstancia en su lugar en desplazamientos

            this->VelocidadDeCola = 0.f;

            if (this->VelocidadActual >= 0.01f) {
                this->VelocidadActual = this->VelocidadDeInstancia;
            }

        }


    } else {


        // Settear el bot que le sigue a null

        if (this->LideraA) {
            this->LideraA = nullptr;
        }

        if (!this->LideradoPor) {

            // Si no tiene lider, ya no avanza en cola por lo que cambia la variable de velocidad a usar a la VelocidadDeinstancia en vez de Cola.

            this->VelocidadDeCola = 0.f;

            if (this->VelocidadActual >= 0.01f) {
                this->VelocidadActual = this->VelocidadDeInstancia;
            }
        }


    }
}


void ARobot::EnChoque(UPrimitiveComponent* ComponenteNuestro, AActor* OtroActor, UPrimitiveComponent* OtroComponente, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Resultado) {
    
    // Procesar colisión entre robots para encolarlos (se llama desde ambos robots chocados a la vez)


    ARobot* OtroRobot = Cast<ARobot>(OtroActor);



    // Comprobar que se ha chocado contra otro robot y no otra cosa

    if (OtroRobot) {
       

        // Se chocó contra otro robot, ver si voy delante o detrás

        if (this->GetActorLocation().Y < OtroActor->GetActorLocation().Y) {
           
            // Esta instancia está delante, lidera a otra y settea su velocidad a la de la cola.


            if (!this->LideraA) {
                this->LideraA = OtroRobot;

                this->DarInfoDeColaASubordinado(this->LideraA);


            }


        } else {
            // Esta instancia está detrás

            if (!this->LideradoPor) {

                this->LideradoPor = OtroRobot;

                // Esclavizar el robot al de delante


            }


        }
    }



}

void ARobot::DarInfoDeColaASubordinado(ARobot* Subordinado) {



    if (this->EsLider()) {
        this->SetVelocidadDeCola(this->VelocidadDeInstancia);


    } else {
        Subordinado->SetVelocidadDeCola(this->VelocidadDeCola);

    }

}

void ARobot::SetVelocidadDeCola(float Vel) {


    // Pone la velocidad de cola a Vel y prograga dicho valor hacia atrás de la cola

    this->VelocidadDeCola = Vel; 

    if (this->VelocidadActual > 0.01f) {
        this->VelocidadActual = Vel;
    }

    if (this->LideraA) {
        this->LideraA->SetVelocidadDeCola(Vel);
    }

}


void ARobot::QuitarIA() {
    Super::QuitarIA();

    // En los robots, al quitar IA se debe quitar la animacion de moverse tmb
    Super::RealizarAnimacion(2); 

}

void ARobot::SetOleada(int Ole) {

    // Settear el atributo de oleada en el que spawnea

    this->Oleada = Ole;
}


int ARobot::GetOleada() {
    return this->Oleada;
}


void ARobot::Parar() {
    

    this->VelocidadActual = 0;
    Super::ClearTimer();
    Super::RealizarAnimacion(2); // QUitar animacion de las ruedas

}

void ARobot::SetVelocidad(float Vel) {
    this->VelocidadDeInstancia = Vel;
    this->VelocidadDeCola = 0.f;
}

void ARobot::ProcesarFinDeVida() {

    // Si un robot llega a su fin de vida, quitarse de las referencias de la cola

    if (this->LideraA) {
        this->LideraA->DeshacerEnlaceDeCola(true);
    }

    if (this->LideradoPor) {
        this->LideradoPor->DeshacerEnlaceDeCola(false);
    }


    // Después, puede proceder a matarse.

    Super::ProcesarFinDeVida();

}


void ARobot::Matar() {

    this->RealizarAnimacion(2); // Parar la animacion de las ruedas
    Super::Matar();
}


ARobot* ARobot::GetLideraA() {return this->LideraA;}


// Métodos de IA:

bool ARobot::HaMovidoEnVerticalDistanciaX(float Distancia) {

    return this->DistanciaRecorridaVertical >= Distancia;
}

void ARobot::InicializarMoverVertical() {
    Super::ClearTimer();
    this->DistanciaRecorridaVertical = 0.f;
    this->VelocidadActual = 750;

    Super::RealizarAnimacion(1); // Animar el robot para que se mueva (loop)
 

    float DeltaTiempo =  UGameplayStatics::GetWorldDeltaSeconds(this) * 1.3f;
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ARobot::MoverVertical, DeltaTiempo);    
    Super::ProgramarTimer(Delegate, DeltaTiempo, true);

}




void ARobot::InicializarMover() {

    Super::ClearTimer();
    Super::RealizarAnimacion(1); // Animar el robot para que se mueva (loop)

    if (this->VelocidadDeCola > 0.01f) {
        this->VelocidadActual = this->VelocidadDeCola;

    } else {
        this->VelocidadActual = this->VelocidadDeInstancia;

    }


    float DeltaTiempo =  UGameplayStatics::GetWorldDeltaSeconds(this) * 1.3f;
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &ARobot::Mover, DeltaTiempo); // Actualizar move 3 de cada 4 frames aproximadamente para ahorrar recursos
    Super::ProgramarTimer(Delegate, DeltaTiempo, true);

    
}

void ARobot::Mover(float DeltaTime) {

    FVector Pos = FVector(0, - this->VelocidadActual * DeltaTime,0);
    this->AddActorWorldOffset(Pos);

}

void ARobot::MoverVertical(float DeltaTime) {

    FVector Pos = FVector(-this->VelocidadActual * DeltaTime, 0 ,0);
    this->AddActorWorldOffset(Pos);
    this->DistanciaRecorridaVertical = this->DistanciaRecorridaVertical + this->VelocidadActual * DeltaTime;

}

bool ARobot::EsLider() {
    return this->LideradoPor == nullptr;
}

float ARobot::ObtenerVidaMaxima() {
    return FindComponentByClass<UComponenteVida>()->ObtenerVidaMaxima();
    
}
