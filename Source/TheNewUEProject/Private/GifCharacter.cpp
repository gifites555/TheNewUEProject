// Fill out your copyright notice in the Description page of Project Settings.


#include "GifCharacter.h"
#include "Camera/CameraComponent.h"	
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AGifCharacter::AGifCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void AGifCharacter::BeginPlay()
{


	Super::BeginPlay();
	
}

void AGifCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);


}

// Called every frame
void AGifCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGifCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGifCharacter::MoveForward);

}

