#include "GifCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/KismetMathLibrary.h"

// Подключение нужных компонентов к Пешке
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

    // Настройка камеры в режиме прицеливания
    bIsAiming = false;

    AimingCameraOffset = FVector(0.0f, 50.0f, 50.0f); // Смещение камеры при прицеливании
    CameraZoomSpeed = 10.0f; // Скорость приближения камеры
    MaxCameraOffset = FVector(0.0f, 50.0f, 50.0f);  // Максимальное смещение камеры при прицеливании

}

// Вызывается при запуске игры или при появлении
void AGifCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Сохраняем изначальное положение камеры (мировое)
    DefaultCameraOffset = SpringArmComp->SocketOffset; // Смещение камеры
    DefaultArmLength = SpringArmComp->TargetArmLength; // Длина SpringArm
}

// Логика для передвижения вперед
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

// Логика для передвижения влево и вправо
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

// Логика стрельбы
void AGifCharacter::PrimaryAttack()
{
    FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_Front");

    FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    GetWorld()->SpawnActor<AActor>(ProjectlieClass, SpawnTM, SpawnParams);
}

// Логика стрельбы через SpecialAttack
void AGifCharacter::SpecialAttack()
{
    FVector CameraLocation = CameraComp->GetComponentLocation();

    FTransform SpawnTM = FTransform(GetControlRotation(), CameraLocation);
    // Здесь можно добавить логику спавна другого типа снаряда или эффекта
}

// Прицеливание
void AGifCharacter::StartAiming()
{
    bIsAiming = true;
    bUseControllerRotationYaw = true;
    GetCharacterMovement()->bOrientRotationToMovement = false;

    FVector TargetCameraOffset = MaxCameraOffset;
    SpringArmComp->SocketOffset = FMath::VInterpTo(SpringArmComp->SocketOffset, TargetCameraOffset, GetWorld()->GetDeltaSeconds(), CameraZoomSpeed);
}


// Остановка прицеливания
void AGifCharacter::StopAiming()
{
    bIsAiming = false;
    bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;

    // Отключаем коллизии SpringArm, чтобы избежать перемещения камеры
    SpringArmComp->bDoCollisionTest = false;

    // Возвращаем камеру в исходные настройки напрямую, без интерполяции
    SpringArmComp->SocketOffset = DefaultCameraOffset;
    SpringArmComp->TargetArmLength = DefaultArmLength;
}

// Вызывается каждый кадр
void AGifCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsAiming)
    {
        // Ограничиваем камеру заданным максимальным смещением
        FVector TargetCameraOffset = MaxCameraOffset;
        SpringArmComp->SocketOffset = FMath::VInterpTo(SpringArmComp->SocketOffset, TargetCameraOffset, DeltaTime, CameraZoomSpeed);
    }
}
// Для подключения нужных функциональностей к персонажу
void AGifCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Вперед - Влево - Вправо
    PlayerInputComponent->BindAxis("MoveForward", this, &AGifCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRAL", this, &AGifCharacter::MoveRAL);

    // Повороты камеры
    PlayerInputComponent->BindAxis("Turn", this, &AGifCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("Up", this, &AGifCharacter::AddControllerPitchInput);

    // Выстрел
    PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AGifCharacter::PrimaryAttack);

    // Выстрел через правую кнопку мыши
    PlayerInputComponent->BindAction("SpecialAttack", IE_Pressed, this, &AGifCharacter::SpecialAttack);

    // Прицеливание
    PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AGifCharacter::StartAiming);
    PlayerInputComponent->BindAction("Aim", IE_Released, this, &AGifCharacter::StopAiming);
}
