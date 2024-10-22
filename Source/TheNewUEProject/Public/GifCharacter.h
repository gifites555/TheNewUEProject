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
	FVector AimingCameraOffset = FVector(0.0f, 50.0f, 50.0f);  // �������� ������ ��� ������������
	FVector MaxCameraOffset;   // ������������ �������� ������ ��� ������������
	FVector DefaultCameraOffset;   // ����������� ���������� ������


	// ������ ���� float, � �� FVector, ��� ��� ��� ����� SpringArm
	float DefaultArmLength;  // ����������� ����� SpringArm

	UPROPERTY(EditAnywhere)
	float CameraZoomSpeed = 10.0f;  // �������� ����������� ������

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