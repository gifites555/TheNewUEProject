

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GifCharMagThir.generated.h"


class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;


UCLASS()
class THENEWUEPROJECT_API AGifCharMagThir : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AGifCharMagThir();

protected:
	
	UPROPERTY(VisibleAnyWhere)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnyWhere)
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovement;


	virtual void BeginPlay() override;


public:	
	
	virtual void Tick(float DeltaTime) override;

};
