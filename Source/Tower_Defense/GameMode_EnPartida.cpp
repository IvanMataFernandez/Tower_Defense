// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode_EnPartida.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonReader.h"


#include "Engine.h"


// Para crear un random int entre 0 y 4 (ambos inclusive):

//#include "Math/UnrealMathUtility.h"
//FMath::RandRange(0, 4);


// Called when the game starts or when spawned
void AGameMode_EnPartida::BeginPlay()
{
	Super::BeginPlay();
    this->CargarNivel();
           

}

void AGameMode_EnPartida::CargarNivel() {

    FString FilePath = FPaths::ProjectContentDir() + TEXT("/Niveles/Archivo.json"); // Ruta del archivo de texto, asegúrate de que esté en la carpeta Content de tu proyecto
    FString Contenido;
    if (FFileHelper::LoadFileToString(Contenido, *FilePath)) {
        TSharedPtr<FJsonObject> JsonNivel;


        if (FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Contenido), JsonNivel)) {
            UE_LOG(LogTemp, Warning, TEXT("Success!"));
            int val;
            JsonNivel->TryGetNumberField(TEXT("Hello"), val);
            UE_LOG(LogTemp, Warning, TEXT("%d"), val);


        } else {
            UE_LOG(LogTemp, Warning, TEXT("ERROR"));

        }



    } else {
        UE_LOG(LogTemp, Warning, TEXT("ERROR"));

    }





    /*
    FString FilePath = FPaths::ProjectContentDir() + TEXT("/DatosNiveles/archivo.txt"); // Ruta del archivo de texto, asegúrate de que esté en la carpeta Content de tu proyecto
    FString Contenido;


    if (FFileHelper::LoadFileToString(Contenido, *FilePath)) {
   
        // El archivo se cargó exitosamente, ahora puedes usar FileContent
        UE_LOG(LogTemp, Warning, TEXT("Contenido del archivo: %s"), *Contenido);
       






        TArray<FString> Lineas;
        Contenido.ParseIntoArray(Lineas, TEXT("\n"), true); // Dividir por saltos de linea;






        for (int F = 0; F != Lineas.Num(); F++) { // Iterar por cada linea
 
            FString Linea = Lineas[F];
            Linea.RemoveFromEnd(TEXT("\n")); // Quitar caracter de salto de linea
   




            TArray<FString> Palabras;
            Linea.ParseIntoArray(Palabras, TEXT(" "), true); // Dividir por espacios




            for (int P = 0; P != Palabras.Num(); P++) { // Iterar por cada palabra
                FString Palabra = Palabras[P];




                // Parsear la palabra a int (debe ser un entero)


                int32 MiInt = FCString::Atoi(*Palabra);
                UE_LOG(LogTemp, Display, TEXT("%d"), MiInt);
               
                // Parsear la palabra a bool (debe ser 0 o 1)


                bool ValorBool = FCString::ToBool(*Palabra);


                if (ValorBool) {
                    UE_LOG(LogTemp, Display, TEXT("true"));
                } else {
                    UE_LOG(LogTemp, Display, TEXT("false"));


                }




            }
        }

    } else {
   
        // Manejar el caso de que el archivo no se pueda cargar
        UE_LOG(LogTemp, Error, TEXT("No se pudo cargar el archivo: %s"), *FilePath);
    }
    */
}