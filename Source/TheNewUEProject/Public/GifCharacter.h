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
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

protected:
	bool bIsAiming = false;

	UPROPERTY(EditAnywhere)
	FVector AimingCameraOffset = FVector(0.0f, 50.0f, 50.0f);  // Смещение камеры при прицеливании
	FVector MaxCameraOffset;   // Максимальное смещение камеры при прицеливании
	FVector DefaultCameraOffset;   // Изначальные координаты камеры


	// Должно быть float, а не FVector, так как это длина SpringArm
	float DefaultArmLength;  // Изначальная длина SpringArm

	UPROPERTY(EditAnywhere)
	float CameraZoomSpeed = 10.0f;  // Скорость приближения камеры

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRAL(float Value);

	void PrimaryAttack();
	void SpecialAttack();

	void StopAiming();
	void StartAiming();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};