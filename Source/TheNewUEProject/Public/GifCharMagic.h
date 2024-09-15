
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GifCharMagic.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class THENEWUEPROJECT_API AGifCharMagic : public AActor
{
	GENERATED_BODY()

public:


	AGifCharMagic();

protected:

	UPROPERTY(VisibleAnyWhere)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnyWhere)
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp;

	
	virtual void BeginPlay() override;

	


public:


	virtual void Tick(float DeltaTime) override;

};