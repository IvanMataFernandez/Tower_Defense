// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Entidad.generated.h"
class UBoxComponent;
class UStaticMeshComponent;
class USceneComponent;
class UAudioComponent;
class AMandoDeIA;



UCLASS()
class TOWER_DEFENSE_API AEntidad : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEntidad();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



// Componentes:

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* PosicionBase;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAudioComponent* ComponenteDeAudio;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* CuerpoBase;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* Hitbox;








// Atrubutos:


private:

	// Referir a ConstructoraDeBlueprints para info de IDs.
	UPROPERTY(EditDefaultsOnly, Category = "ID")
	uint8 ID;



	UPROPERTY(EditDefaultsOnly, Category = "Datos")
	float TiempoDeAnimacionDeMuerte = 1.f;



	FTimerHandle TimerFrame;

	static float VolumenEfectos;

	AMandoDeIA* MandoDeIA;

// Métodos:

protected:


	virtual void Matar();
	virtual void AutoDestruir();


	UFUNCTION(BlueprintImplementableEvent)
	void DestruirAnimaciones();



	void ClearTimer();
	void Invisibilizar();
	void SetVulnerable(bool Vulnerable);
	void VisibilizarATorres();
	void DesactivarHitbox();
	void Destruir();
	uint8 ObtenerID();

	void ProgramarTimer(FTimerDelegate Delegate, float TiempoDeEspera, bool EnBucle);

	void ProgramarTimerFinDeTareaIA(float TiempoEspera); 



public:

	UFUNCTION(BlueprintCallable)
	static void SetVolumenEfectosDeEntidades(float Vol, UObject* ContextoMundo);
	
	virtual void ProcesarFinDeVida();

	virtual void QuitarIA();


	void PausarEntidad();
    void DespausarEntidad();
	
	UFUNCTION(BlueprintImplementableEvent)
	void RealizarAnimacion(int Animacion);

	AMandoDeIA* GetMandoDeIA();

	FVector ObtenerRadioHitbox();

};
