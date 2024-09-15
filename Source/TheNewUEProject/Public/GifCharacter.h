// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GifCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class THENEWUEPROJECT_API AGifCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGifCharacter();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectlieClass;


protected:
	UPROPERTY(VisibleAnyWhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnyWhere)
	USpringArmComponent* SpringArmComp;	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRAL(float Value);

	void PrimaryAttack();



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
