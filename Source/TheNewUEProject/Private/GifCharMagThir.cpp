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
 	
	PrimaryActorTick.bCanEverTick = true;

    SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
    SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
    
    SphereComp->SetCollisionProfileName("Projectile");

    RootComponent = SphereComp;

    EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
    EffectComp->SetupAttachment(SphereComp);


    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
    MovementComp->InitialSpeed = 1000.0f;
    MovementComp->bRotationFollowsVelocity = true;
    MovementComp->bInitialVelocityInLocalSpace = true;
}


void AGifCharMagThir::BeginPlay()
{
	Super::BeginPlay();

    if (ProjectileMovement)
    {
        ProjectileMovement->ProjectileGravityScale = 0.0f;
    }
	
}


void AGifCharMagThir::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

