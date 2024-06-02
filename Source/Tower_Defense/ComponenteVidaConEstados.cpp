// Fill out your copyright notice in the Description page of Project Settings.


#include "ComponenteVidaConEstados.h"
#include "Math/UnrealMathUtility.h"
#include "Robot.h"



// Componente que maneja la vida de las entidades. Hereda del componente anterior, para incluir también llamadas a animaciones exclusivas
// que cambian el aspecto de la entidad según cuanto daño porcentual haya absorbido

void UComponenteVidaConEstados::BeginPlay()
{
	Super::BeginPlay();
    this->Estado = this->NumEstados; // Num estados guarda la cantidad de estados visuales que tiene una entidad (definido por blueprint según la entidad en concreto)
                                    // Los estados se dividen equivalentemente entre toda la vida disponible

}


void UComponenteVidaConEstados::AplicarDano(AActor* Danado, float DanoBase, const UDamageType* TipoDano, AController* Instigator, AActor* Causador) {

    Super::AplicarDano(Danado, DanoBase, TipoDano, Instigator, Causador); // Procesar el daño absorbido en la clase padre

    // Calcular en que estado cae la entidad ahora según su vida restante

    int ThresholdVida = FMath::Floor(Super::ObtenerFraccionVidaRestante() * this->NumEstados)+1;

    if (ThresholdVida < this->Estado) {

        // Si cae al menos un estado por debajo de lo que está, actualizar su estado y realizar la animación correspondiente para cambiar el aspecto visual de la entidad
        this->Estado = ThresholdVida;
        Cast<AEntidad>(this->GetOwner())->RealizarAnimacion(this->Estado * -1);
    }
    


}