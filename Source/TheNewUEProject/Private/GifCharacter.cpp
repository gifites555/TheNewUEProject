#include "GifCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/KismetMathLibrary.h"

// ����������� ������ ����������� � �����
AGifCharacter::AGifCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
    SpringArmComp->SetupAttachment(RootComponent);

    CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
    CameraComp->SetupAttachment(SpringArmComp);

    SpringArmComp->bUsePawnControlRotation = true;
    SpringArmComp->bInheritPitch = true;
    SpringArmComp->bInheritYaw = true;
    SpringArmComp->bInheritRoll = true;

    GetCharacterMovement()->bOrientRotationToMovement = true;

    bUseControllerRotationYaw = false;

    // ��������� ������ � ������ ������������
    bIsAiming = false;

    AimingCameraOffset = FVector(0.0f, 50.0f, 50.0f); // �������� ������ ��� ������������
    CameraZoomSpeed = 10.0f; // �������� ����������� ������
    MaxCameraOffset = FVector(0.0f, 50.0f, 50.0f);  // ������������ �������� ������ ��� ������������

}

// ���������� ��� ������� ���� ��� ��� ���������
void AGifCharacter::BeginPlay()
{
    Super::BeginPlay();

    // ��������� ����������� ��������� ������ (�������)
    DefaultCameraOffset = SpringArmComp->SocketOffset; // �������� ������
    DefaultArmLength = SpringArmComp->TargetArmLength; // ����� SpringArm
}

// ������ ��� ������������ ������
void AGifCharacter::MoveForward(float Value)
{
    if (Controller && Value != 0.0f)
    {
        FRotator CameraRotation = Controller->GetControlRotation();

        FRotator YawRotation(0, CameraRotation.Yaw, 0);

        FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

        AddMovementInput(Direction, Value);
    }
}

// ������ ��� ������������ ����� � ������
void AGifCharacter::MoveRAL(float Value)
{
    if (Controller && Value != 0.0f)
    {
        FRotator CameraRotation = Controller->GetControlRotation();

        FRotator YawRotation(0, CameraRotation.Yaw, 0);
        FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(Direction, Value);
    }
}

// ������ ��������
void AGifCharacter::PrimaryAttack()
{
    FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_Front");

    FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    GetWorld()->SpawnActor<AActor>(ProjectlieClass, SpawnTM, SpawnParams);
}

// ������ �������� ����� SpecialAttack
void AGifCharacter::SpecialAttack()
{
    FVector CameraLocation = CameraComp->GetComponentLocation();

    FTransform SpawnTM = FTransform(GetControlRotation(), CameraLocation);
    // ����� ����� �������� ������ ������ ������� ���� ������� ��� �������
}

// ������������
void AGifCharacter::StartAiming()
{
    bIsAiming = true;
    bUseControllerRotationYaw = true;
    GetCharacterMovement()->bOrientRotationToMovement = false;

    FVector TargetCameraOffset = MaxCameraOffset;
    SpringArmComp->SocketOffset = FMath::VInterpTo(SpringArmComp->SocketOffset, TargetCameraOffset, GetWorld()->GetDeltaSeconds(), CameraZoomSpeed);
}


// ��������� ������������
void AGifCharacter::StopAiming()
{
    bIsAiming = false;
    bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;

    // ��������� �������� SpringArm, ����� �������� ����������� ������
    SpringArmComp->bDoCollisionTest = false;

    // ���������� ������ � �������� ��������� ��������, ��� ������������
    SpringArmComp->SocketOffset = DefaultCameraOffset;
    SpringArmComp->TargetArmLength = DefaultArmLength;
}

// ���������� ������ ����
void AGifCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsAiming)
    {
        // ������������ ������ �������� ������������ ���������
        FVector TargetCameraOffset = MaxCameraOffset;
        SpringArmComp->SocketOffset = FMath::VInterpTo(SpringArmComp->SocketOffset, TargetCameraOffset, DeltaTime, CameraZoomSpeed);
    }
}
// ��� ����������� ������ ����������������� � ���������
void AGifCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // ������ - ����� - ������
    PlayerInputComponent->BindAxis("MoveForward", this, &AGifCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRAL", this, &AGifCharacter::MoveRAL);

    // �������� ������
    PlayerInputComponent->BindAxis("Turn", this, &AGifCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("Up", this, &AGifCharacter::AddControllerPitchInput);

    // �������
    PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AGifCharacter::PrimaryAttack);

    // ������� ����� ������ ������ ����
    PlayerInputComponent->BindAction("SpecialAttack", IE_Pressed, this, &AGifCharacter::SpecialAttack);

    // ������������
    PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AGifCharacter::StartAiming);
    PlayerInputComponent->BindAction("Aim", IE_Released, this, &AGifCharacter::StopAiming);
}
