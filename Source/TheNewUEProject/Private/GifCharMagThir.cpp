// Fill out your copyright notice in the Description page of Project Settings.


#include "GifCharMagThir.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"


AGifCharMagThir::AGifCharMagThir()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
    RootComponent = SphereComp;

    EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
    EffectComp->SetupAttachment(SphereComp);

    MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
    MovementComp->InitialSpeed = 1000.0f;
    MovementComp->bRotationFollowsVelocity = true;
    MovementComp->bInitialVelocityInLocalSpace = true;
}

// Called when the game starts or when spawned
void AGifCharMagThir::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGifCharMagThir::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

