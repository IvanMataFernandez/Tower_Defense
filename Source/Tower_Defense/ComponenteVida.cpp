// Fill out your copyright notice in the Description page of Project Settings.


#include "ComponenteVida.h"
#include "Entidad.h"


// Componente que maneja la vida de las entidades.

// Sets default values for this component's properties
UComponenteVida::UComponenteVida()
{

	PrimaryComponentTick.bCanEverTick = false; 
	this->Vulnerable = true;

}


// Called when the game starts
void UComponenteVida::BeginPlay()
{
	Super::BeginPlay();
	this->Vida = this->VidaMaxima; // Poner la vida de la entidad al 100%
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UComponenteVida::AplicarDano); // Bindear evento de daño al método de abajo


}


bool UComponenteVida::EsVulnerable() {return this->Vulnerable;}

void UComponenteVida::SetVulnerable(bool Vul) {this->Vulnerable = Vul;}

bool UComponenteVida::EstaVivo() {
	return this->Vida > 0.f;
}

void UComponenteVida::AplicarDano(AActor* Danado, float DanoBase, const UDamageType* TipoDano, AController* Instigator, AActor* Causador) {

	// Aplicar daño absorbido, si la entidad está en un estado invulnerable (una mina que ya se ha descubierto, un robot ocultador con su escudo cerrado...)
	// entonces no puede absorber daño y se salta la este método entero para omitir daño




	if (this->Vulnerable) {

		// Es vulnerable, aplicar el daño absorbido

		if (this->Vida > DanoBase) {
			this->UltimoDanoAbsorbido = DanoBase;
			this->Vida -= this->UltimoDanoAbsorbido;


		} else {
			this->UltimoDanoAbsorbido = this->Vida;
			this->Vida = 0.f;

			// Si baja por debajo de 0 de vida, entonces procesar el método que acaba con la vida de la entidad.
			Cast<AEntidad>(GetOwner())->ProcesarFinDeVida();

			// Hacer la entidad inmune a todo daño para que por sí hace una animación de muerte o está todavía un rato en la pantalla, que no vuelva a activar
			// la lógica de empezar a matarla si la hitbox absorbe más daño.

			this->SetVulnerable(false);

		}
	
	} else {
		this->UltimoDanoAbsorbido = -1.f;
	}





}


float UComponenteVida::ObtenerVidaMaxima() {
	return this->VidaMaxima;
}



float UComponenteVida::ObtenerUltimoDanoRecibido() {
	return this->UltimoDanoAbsorbido;
}

float UComponenteVida::ObtenerFraccionVidaRestante() {
	if (this->Vida > 0) {
		return this->Vida / this->VidaMaxima;

	} else {
		return 0.f;
	}
}





