// Fill out your copyright notice in the Description page of Project Settings.


#include "Casilla.h"

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
        AActor* Hijo = AActor::GetWorld()->SpawnActor<AActor>(ACasilla::StaticClass(), FVector(Pos.X,Pos.Y,Pos.Z+100), FRotator(0,0,0)) ;
        Hijo->SetOwner(this);
        this->Torre = Hijo;




        UE_LOG(LogTemp, Warning, TEXT("Spawned!"));


        return true;
    } else {


      //  this->Torre->SetOwner(nullptr);
      //  this->Torre->Destroy();
      //  this->Torre = nullptr;




        UE_LOG(LogTemp, Warning, TEXT("YA HAY ALGO!"));


        return false;
    }



}
