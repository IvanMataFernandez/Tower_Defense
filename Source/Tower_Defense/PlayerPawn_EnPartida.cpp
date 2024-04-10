// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn_EnPartida.h"
#include "Casilla.h"
#include "MandoDeJugador_EnPartida.h"
#include "Kismet/GameplayStatics.h"

#include "Camera/CameraComponent.h"
#include "GameMode_EnPartida.h"

/*

		En preview:

		Position: -1311.746828, 2177.097946, 1899.845983
		Rotation: 0, -57.600855 °, 0


		En partida:
		
	    Position: -546.010253 -376.218195 2719.0
	    Rotation:        0, -71.523093 °  ,0


*/



// Sets default values
APlayerPawn_EnPartida::APlayerPawn_EnPartida()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	this->Camara = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    RootComponent = Camara;
}

// Called when the game starts or when spawned
void APlayerPawn_EnPartida::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn_EnPartida::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn_EnPartida::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("Pinchar"), IE_Pressed, this, &APlayerPawn_EnPartida::Pinchar);

}

void APlayerPawn_EnPartida::Pinchar() {
	Cast<AMandoDeJugador_EnPartida>(UGameplayStatics::GetPlayerController(this, 0))->Pinchar();

}

void APlayerPawn_EnPartida::MoverCamASeleccion() {

	FVector Loc = this->GetActorLocation();

	FTimerHandle Timer1;
	FTimerHandle Timer2;
	FTimerHandle Timer3;
	FTimerHandle LlamadaAGameMode;


	// Moverse Primero de lado
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &APlayerPawn_EnPartida::MoverCamA, -545.f, 2178.f, 2719.0f, 3.f);
    GetWorld()->GetTimerManager().SetTimer(Timer1, Delegate, 0.01f, false);   


	// Luego poner la camara más abajo y rotarla hacia arriba

    FTimerDelegate Delegate2 = FTimerDelegate::CreateUObject(this, &APlayerPawn_EnPartida::MoverCamA, -1312.f, 2178.f, 1900.f, 1.0f);
    GetWorld()->GetTimerManager().SetTimer(Timer2, Delegate2, 3.f, false);   
	

    FTimerDelegate Delegate3 = FTimerDelegate::CreateUObject(this, &APlayerPawn_EnPartida::RotarCamEnPitchA, -57.f, 1.0f);
    GetWorld()->GetTimerManager().SetTimer(Timer3, Delegate3, 3.f, false);   



	// Finalmente llamar al gamemode para empezar con la seleccion de torres


    GetWorld()->GetTimerManager().SetTimer(LlamadaAGameMode, Cast<AGameMode_EnPartida>(GetWorld()->GetAuthGameMode()), &AGameMode_EnPartida::EmpezarSeleccionDeTorres, 4.f, false);

}
void APlayerPawn_EnPartida::MoverCamAJugar() {

	FVector Loc = this->GetActorLocation();

	FTimerHandle Timer1;
	FTimerHandle Timer2;
	FTimerHandle Timer3;
	FTimerHandle LlamadaAGameMode;


	// Moverse Primero hacia arriba

    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &APlayerPawn_EnPartida::MoverCamA, -546.f, 2178.f, 2719.f, 1.0f);
    GetWorld()->GetTimerManager().SetTimer(Timer2, Delegate, 0.01f, false);   
	

    FTimerDelegate Delegate2 = FTimerDelegate::CreateUObject(this, &APlayerPawn_EnPartida::RotarCamEnPitchA, -71.f, 1.0f);
    GetWorld()->GetTimerManager().SetTimer(Timer3, Delegate2, 0.01f, false);   


	// Luego moverse de lado

    FTimerDelegate Delegate3 = FTimerDelegate::CreateUObject(this, &APlayerPawn_EnPartida::MoverCamA, -546.f, -376.f, 2719.0f, 1.5f);
    GetWorld()->GetTimerManager().SetTimer(Timer1, Delegate3, 1.f, false);   



	// Finalmente llamar al gamemode para empezar con el juego


    GetWorld()->GetTimerManager().SetTimer(LlamadaAGameMode, Cast<AGameMode_EnPartida>(GetWorld()->GetAuthGameMode()), &AGameMode_EnPartida::CargarCuentaAtrasParaEmpezarJuego, 2.5f, false);


}

void APlayerPawn_EnPartida::MoverCamAIzquierda() {
	FVector Loc = this->GetActorLocation();

	FTimerHandle Timer1;

	FTimerHandle LlamadaAGameMode;


	// Mover de lado

	FTimerDelegate Delegate3 = FTimerDelegate::CreateUObject(this, &APlayerPawn_EnPartida::MoverCamA, -546.f, -1317.f, 2719.0f, 3.f);
    GetWorld()->GetTimerManager().SetTimer(Timer1, Delegate3, 1.f, false);   


	// Finalmente llamar al gamemode para mostrar la UI de derrota

    GetWorld()->GetTimerManager().SetTimer(LlamadaAGameMode, Cast<AGameMode_EnPartida>(GetWorld()->GetAuthGameMode()), &AGameMode_EnPartida::FocusearCausanteDerrota, 5.f, false);

}


void APlayerPawn_EnPartida::MoverCamA(float X, float Y, float Z, float Duracion) {
	
	FVector Loc = this->GetActorLocation();

	this->TiempoAct = 0.f;
	this->TiempoTotal = Duracion;

	// Mover
	this->VelX = ((X) - Loc.X) / Duracion * this->DeltaTiempo;
	this->VelY = ((Y) - Loc.Y) / Duracion * this->DeltaTiempo;
	this->VelZ = ((Z) - Loc.Z) / Duracion * this->DeltaTiempo;

    GetWorld()->GetTimerManager().SetTimer(this->Timer, this, &APlayerPawn_EnPartida::MoverCam, this->DeltaTiempo, true);


}


void APlayerPawn_EnPartida::MoverCam() {


	FVector Loc = this->GetActorLocation();
	

	this->SetActorLocation(FVector(Loc.X+this->VelX, Loc.Y+this->VelY, Loc.Z+this->VelZ));
	

	this->TiempoAct = this->TiempoAct + this->DeltaTiempo;

	if (this->TiempoAct >= this->TiempoTotal) {
		GetWorldTimerManager().ClearTimer(this->Timer);

	}
}


