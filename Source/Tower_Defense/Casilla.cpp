// Fill out your copyright notice in the Description page of Project Settings.


#include "Casilla.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Torre.h"



#include "ConstructoraDeBlueprints.h"


// Sets default values
ACasilla::ACasilla()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Settear el mesh
	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = this->Mesh;

}

// Called when the game starts or when spawned
void ACasilla::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACasilla::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ACasilla::IntentarColocarTorre() {


    if (!this->Torre) {

		// TODO: Llamar a Controller para obtener la clase c++ y blueprint de la torre a spawnear en la seleccion

        FVector Pos = AActor::GetActorLocation();
        this->SpawnearTorre(11); // Por ahora spawnea bombas, settear la torre elegida en UI después

        /*
          Se spawnea la instancia blueprint en un metodo blueprint, ejecuta:
          AActor* Hijo = GetWorld()->SpawnActor<AActor>(ClaseBlueprintCorrespondienteAID, FVectorDeCasilla+(Z+100), FRotator(0,0,0));
       
        */
         this->Torre->SetOwner(this);

        return true;
    } else {

      // Considerar un if block aquí de sí pala o equivalente seleccionado entonces => this->Torre->Matar()   [Matar tiene toda la logica necesaria para quitar la torre]

      //  this->Torre->SetOwner(nullptr);
      //  this->Torre->Destroy();
      //  this->Torre = nullptr;




        UE_LOG(LogTemp, Warning, TEXT("YA HAY ALGO!"));


        return false;
    }



}


void ACasilla::LiberarCasilla() {
  // This->Torre Llama aquí para quitarse de la casilla

  this->Torre->SetOwner(nullptr);
  this->Torre = nullptr;



}



