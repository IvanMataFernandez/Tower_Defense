// Fill out your copyright notice in the Description page of Project Settings.


#include "ZonaSpawnRobot.h"
#include "Components/BoxComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Robot.h"
#include "Kismet/GameplayStatics.h"


// La zona invisible que hace aparecer los robots de la partida que vienen desde la derecha


AZonaSpawnRobot::AZonaSpawnRobot()
{
	PrimaryActorTick.bCanEverTick = false;
	this->ZonaDeSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("Zona de Spawn"));
	RootComponent = this->ZonaDeSpawn;

}

// Called when the game starts or when spawned
void AZonaSpawnRobot::BeginPlay()
{

	// Calcular los 5 puntos donde pueden aparecer los robots (uno por cada fila)

	Super::BeginPlay();
	this->Radio = this->ZonaDeSpawn->GetScaledBoxExtent();
	float RadioX = this->Radio.X;
	this->TamanoCasillaX = RadioX / 2.5f;

	for (int i = 0; i != 5; i++) {
		PosicionesDeSpawn.Add(RadioX * (0.4 * i - 0.8));
	}


	this->Localizacion = AActor::GetActorLocation();   

	for (int Fila = 0; Fila != 5; Fila++) {
		this->EspacioOcupadoPorFila.Add(100 + FMath::FRand() * 200.f);
	}


}

ARobot* AZonaSpawnRobot::SpawnearRobot(int ID) {

	// Post: Se spawnea el robot de tipo "ID" y se le settea su variable de aparición de oleada a "Oleada".
	//       La fila en la que se spawnea la elige esta clase. Prioriza spawnear en filas en las que van un spawn por detrás
	//       de las demás en la misma oleada.




  	// Antes de spawnear el bot, elegir en que fila va a aparecer. Se intenta repartir el mismo numero de robots por cada fila
    // de manera que si al menos una fila va un spawn por detrás, entonces se elige esa para hacerlo aparecer sobre el resto


    // Elegir entre las filas posibles que van un spawn por detrás
    int IdxFilaDisponibleParaSpawn = FMath::RandRange(0, this->FilasHabilitadasParaSpawn.Num()-1);
    int FilaElegida = this->FilasHabilitadasParaSpawn[IdxFilaDisponibleParaSpawn];

    
    // Quitar dicho valor de fila del array de disponibilidades, para ello se pasa el último elemento del array a la posición del elemento a quitar
    // y se quita el último elemento de la lista. Esto es más eficiente que la forma tradicional de hacerlo (Para hacer coste O(1) ) pero puede
    // alterar el orden de los elementos de la lista (no importa, porque solo nos interesa saber que filas QUEDAN disponibles, NO en que orden)
    
    this->FilasHabilitadasParaSpawn[IdxFilaDisponibleParaSpawn] = this->FilasHabilitadasParaSpawn[this->FilasHabilitadasParaSpawn.Num()-1];
    this->FilasHabilitadasParaSpawn.Pop();


    
    // Si no quedan mas filas donde spawnear, estan todas empatadas por números de robot, volver a refrescar el array de filas disponibles 
	// (permitir spawn en todas las filas)

    if (this->FilasHabilitadasParaSpawn.IsEmpty()) {
        this->FilasHabilitadasParaSpawn.Add(0);
        this->FilasHabilitadasParaSpawn.Add(1);
        this->FilasHabilitadasParaSpawn.Add(2);
        this->FilasHabilitadasParaSpawn.Add(3);
        this->FilasHabilitadasParaSpawn.Add(4);
    }





	/* Calcular la posición de spawn del robot:

		Variables a tener en cuenta:

			- FilaElegida: La fila a donde spawnear el robot (indica offset hacia adelante o atrás desde la POV de la camara)
			- EspacioOcupadoPorFila[FilaElegida]: Respecto a la fila, la posición de profundidad donde la zona de spawn quiere spawnear el siguiente
												  robot 


		Coords:

			X (direccion en la que se extienden las columnas): Hacerlo spawnear en la zona de spawn + offset de tamaño de casilla por la fila (FilaElegida)
															   (la fila del medio no aplica offset, las dos
															   de más arriba aplican offset positivo, las dos de más abajo offset negativo)


			Y (dirección en la que se extienden las filas): Hacerlo aparecer como mínimo en la posición de la zona de spawn. Se le da un offset extra hacia atrás
															en función de la fila elegida a spawnear (EspacioOcupadoPorFila[FilaElegida]).
															Cada vez que spawnea un bot en esa fila en la misma oleada, se incrementa el offset para que el siguiente
															bot spawnee más atrás en esa misma fila.

			Z (la altura): La altura no varía en función de ninguna variable, se spawnea el robot al nivel del suelo siempre

	*/ 

	FVector Pos = FVector(this->Localizacion.X + this->PosicionesDeSpawn[FilaElegida], this->Localizacion.Y - this->Radio.Y  + this->EspacioOcupadoPorFila[FilaElegida] , this->Localizacion.Z - this->Radio.Z );
	
	
	// El bot ya tiene setteadas las coords donde aparecer, incrementar el offset hacia atrás de esa misma fila (por (200-400) unidades)

	this->EspacioOcupadoPorFila[FilaElegida] = this->EspacioOcupadoPorFila[FilaElegida] + 200.f + FMath::FRand() * 200.f;

	return this->MaterealizarRobot(ID, Pos);
	


}


void AZonaSpawnRobot::RefrescarNuevaOleada() {


    // Reiniciar el habilitador de spawn de filas

    this->FilasHabilitadasParaSpawn.Empty();
    this->FilasHabilitadasParaSpawn.Add(0);
    this->FilasHabilitadasParaSpawn.Add(1);
    this->FilasHabilitadasParaSpawn.Add(2);
    this->FilasHabilitadasParaSpawn.Add(3);
    this->FilasHabilitadasParaSpawn.Add(4);


	// Checkear si hay bots por detrás de la zona de spawns, para spawnear los nuevos bots aun más atrás


	TArray<float> AtrasoExtra; // Cada posicion de AtrasoExtra indica por cuanto más habría que poner un bot atrás de lo normal en cada fila. (5 posiciones, 5 filas)

	for (int i = 0; i != 5; i++) {
		AtrasoExtra.Add(0.f);
	}


	TArray<AActor*> Robots;

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARobot::StaticClass(), Robots);

    for (AActor* Entidad : Robots) {
		// Iterar por cada robot para ver donde están

		ARobot* Robot = Cast<ARobot>(Entidad);
		
		FVector PosRobot = Robot->GetActorLocation(); // Obtener pos global del robot

		int Fila = FMath::Floor(((PosRobot.X - this->Localizacion.X + this->Radio.X) / this->TamanoCasillaX)); // Determinar en que fila está basada en las posiciones relativas entre la zona de spawn y el robot en sí
		float DistanciaFondo = (PosRobot.Y - (this->Localizacion.Y - this->Radio.Y)) + Robot->ObtenerRadioHitbox().Y; // Determinar si el robot está delante de la zona de spawn (más cerca de la mina del jugador, resultado negativo)
																													  // o detrás de la zona de spawn (más lejos de la mina del jugador, resultado positivo)




		if (DistanciaFondo > AtrasoExtra[Fila]) { // Si el robot actual está más atrás que el máximo de distancias hacia atrás de los robots de su misma fila evaluados hasta ahora
												  // (El valor por defecto de AtrasoExtra[X] es 0.f, por lo que valores negativos (robots más cerca de la mina del jugador en comparación)
												  // con la zona de spawn no afectan al resultado final)
			
			
			AtrasoExtra[Fila] = DistanciaFondo; // Settear el nuevo máximo
		}
	}

	// Resettear los spawns para decirle a la zona que vuelva a empezar a spawnear bots desde el punto más cercano posible (en la zona de spawn o si hay bots ocupandola ya, detrás de ellos)

	for (int Fila = 0; Fila != this->EspacioOcupadoPorFila.Num(); Fila++) {
		this->EspacioOcupadoPorFila[Fila] = 200 + FMath::FRand() * 200.f + AtrasoExtra[Fila];
	}


}






ARobot* AZonaSpawnRobot::MaterealizarRobot_Implementation(int ID, FVector Posicion) {
	// NOP. Está en blueprint. Genera el robot en sí físicamente según el ID de instancia robot blueprint dada y su posicion en el nivel
	return nullptr;
}


