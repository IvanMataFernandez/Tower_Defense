// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn_EnPartida.h"
#include "Casilla.h"
#include "MandoDeJugador_EnPartida.h"
#include "Kismet/GameplayStatics.h"

#include "Camera/CameraComponent.h"
#include "GameMode_EnPartida.h"



// La clase que es "el jugador en sí". Se trata de un juego de tower defense por lo que no se necesita un personaje muy complejo ni nada, el jugador
// en sí se limita a una camara que se puede mover por el nivel.


/*

		En preview:

		Position: -1741.56, -2373.20, 1935.17
		Rotation: 0, 319.59°, 0


		En partida:

		Antiguo:
		Position:  -267.f, -452.f, 2950.0f
		Rotation: 0, -76, 0


		Nuevo:

		Position: -683.5, -452, 3147.73331
		Rotation: 0, -72.42, 0




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

void APlayerPawn_EnPartida::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	// Vincular la instrucción de click izquierdo del ratón a "Pinchar()"

	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("Pinchar"), IE_Pressed, this, &APlayerPawn_EnPartida::Pinchar);





}

void APlayerPawn_EnPartida::Pinchar() {

	// Si se pincha con click izquierdo del ratón, informar al player controller de ello ya que es el mando el que maneja y controla los clicks en casillas y demás

	Cast<AMandoDeJugador_EnPartida>(UGameplayStatics::GetPlayerController(this, 0))->Pinchar();

}

void APlayerPawn_EnPartida::MoverCamASeleccion() {

	// Mueve la camara desde el punto por defecto al ángulo en el que se ven los robots en preview del nivel

	this->DeltaTiempo = UGameplayStatics::GetWorldDeltaSeconds(this); // Cargar deltatime here porque en BeginPlay() no se puede obtener todavia y esta es la primera
																	 // Instruccion de la clase a ejecutar

	FVector Loc = this->GetActorLocation();


	FTimerHandle Timer1;
	FTimerHandle Timer2;
	FTimerHandle Timer3;
	FTimerHandle LlamadaAGameMode;



	// Moverse Primero de lado
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &APlayerPawn_EnPartida::MoverCamA, -1741.567245f, 2156.f, 1935.176425f, 3.f);
    GetWorld()->GetTimerManager().SetTimer(Timer1, Delegate, 0.01f, false);   


	// Luego poner la camara más abajo y rotarla hacia arriba

    FTimerDelegate Delegate2 = FTimerDelegate::CreateUObject(this, &APlayerPawn_EnPartida::MoverCamA, -1679.f, 2156.f, 2013.f, 1.0f);
    GetWorld()->GetTimerManager().SetTimer(Timer2, Delegate2, 3.f, false);   
	

    FTimerDelegate Delegate3 = FTimerDelegate::CreateUObject(this, &APlayerPawn_EnPartida::RotarCamEnPitchA, 317.f, 1.0f);
    GetWorld()->GetTimerManager().SetTimer(Timer3, Delegate3, 3.f, false);   



	// Finalmente llamar al gamemode para empezar con la seleccion de torres


    GetWorld()->GetTimerManager().SetTimer(LlamadaAGameMode, Cast<AGameMode_EnPartida>(GetWorld()->GetAuthGameMode()), &AGameMode_EnPartida::EmpezarSeleccionDeTorres, 4.f, false);

}
void APlayerPawn_EnPartida::MoverCamAJugar() {


	// Mueve la camara desde el punto de selección de torres al angulo usado durante la partida en sí.

	FVector Loc = this->GetActorLocation();

	FTimerHandle Timer1;
	FTimerHandle Timer2;
	FTimerHandle Timer3;
	FTimerHandle LlamadaAGameMode;


	// Moverse Primero hacia arriba y rotarla

    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &APlayerPawn_EnPartida::MoverCamA, -683.5f, 2156.f, 3147.73331f, 1.0f);
    GetWorld()->GetTimerManager().SetTimer(Timer2, Delegate, 0.01f, false);   
	

    FTimerDelegate Delegate2 = FTimerDelegate::CreateUObject(this, &APlayerPawn_EnPartida::RotarCamEnPitchA, -72.45f, 1.0f);
    GetWorld()->GetTimerManager().SetTimer(Timer3, Delegate2, 0.01f, false);   


	// Luego moverse de lado

    FTimerDelegate Delegate3 = FTimerDelegate::CreateUObject(this, &APlayerPawn_EnPartida::MoverCamA,  -683.5f, -452.f,  3147.73331f, 1.5f);
    GetWorld()->GetTimerManager().SetTimer(Timer1, Delegate3, 1.f, false);   



	// Finalmente llamar al gamemode para empezar con el juego


    GetWorld()->GetTimerManager().SetTimer(LlamadaAGameMode, Cast<AGameMode_EnPartida>(GetWorld()->GetAuthGameMode()), &AGameMode_EnPartida::CargarCuentaAtrasParaEmpezarJuego, 2.5f, false);


}

void APlayerPawn_EnPartida::MoverCamAIzquierda() {

	// Mueve la camara desde la posición donde se ve la partida en sí hasta el ángulo en el que se ve a un robot colarse en la mina del jugador, dándole la derrota


	FVector Loc = this->GetActorLocation();

	FTimerHandle Timer1;

	FTimerHandle LlamadaAGameMode;


	// Mover de lado

	FTimerDelegate Delegate3 = FTimerDelegate::CreateUObject(this, &APlayerPawn_EnPartida::MoverCamA,  -683.5f, -1317.f,  3147.73331f, 3.f);
    GetWorld()->GetTimerManager().SetTimer(Timer1, Delegate3, 1.f, false);   


	// Finalmente llamar al gamemode para mostrar la UI de derrota

    GetWorld()->GetTimerManager().SetTimer(LlamadaAGameMode, Cast<AGameMode_EnPartida>(GetWorld()->GetAuthGameMode()), &AGameMode_EnPartida::FocusearCausanteDerrota, 5.f, false);

}


// Métodos reusados para programar los movimientos de camara constantes durante X tiempo. Incluye traslación y rotación

void APlayerPawn_EnPartida::MoverCamA(float X, float Y, float Z, float Duracion) {
	
	FVector Loc = this->GetActorLocation();

	this->TiempoAct = 0.f;
	this->TiempoTotal = Duracion;

	// Mover
	this->VelX = ((X) - Loc.X) / Duracion * this->DeltaTiempo;
	this->VelY = ((Y) - Loc.Y) / Duracion * this->DeltaTiempo;
	this->VelZ = ((Z) - Loc.Z) / Duracion * this->DeltaTiempo;

	this->PosTarget = FVector(X,Y,Z);

    GetWorld()->GetTimerManager().SetTimer(this->Timer, this, &APlayerPawn_EnPartida::MoverCam, this->DeltaTiempo, true);


}

void APlayerPawn_EnPartida::RotarCamEnPitchA(float Pitch, float Duracion) {
	FRotator Rot = this->Camara->GetRelativeRotation();

	this->TiempoActRot = 0.f;
	this->TiempoTotalRot = Duracion;

	this->VelPitch = (Pitch - Rot.Pitch) / Duracion * this->DeltaTiempo;


    GetWorld()->GetTimerManager().SetTimer(this->TimerRotacion, this, &APlayerPawn_EnPartida::RotarCam, this->DeltaTiempo, true);
	this->RotTarget = FRotator(Pitch,Rot.Yaw,Rot.Roll);

}

void APlayerPawn_EnPartida::MoverCam() {


	FVector Loc = this->GetActorLocation();
	

	this->SetActorLocation(FVector(Loc.X+this->VelX, Loc.Y+this->VelY, Loc.Z+this->VelZ));

	this->TiempoAct = this->TiempoAct + this->DeltaTiempo;

	if (this->TiempoAct >= this->TiempoTotal) {
		GetWorldTimerManager().ClearTimer(this->Timer);
		this->SetActorLocation(this->PosTarget);

	}
}

void APlayerPawn_EnPartida::RotarCam() {
	
	FRotator Rot = this->Camara->GetRelativeRotation();
	this->Camara->SetWorldRotation(FRotator(Rot.Pitch+this->VelPitch,0 , 0));

	this->TiempoActRot = this->TiempoActRot + this->DeltaTiempo;

	if (this->TiempoActRot >= this->TiempoTotalRot) {
		GetWorldTimerManager().ClearTimer(this->TimerRotacion);
		this->SetActorRotation(this->RotTarget);

	}


}





