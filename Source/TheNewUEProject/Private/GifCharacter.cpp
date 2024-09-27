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
    
   
}

// Вызывается при запуске игры или при появлении
void AGifCharacter::BeginPlay()
{
    Super::BeginPlay();
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

void AGifCharacter::PrimaryAttack()
{

    FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_Front");

    FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

    FActorSpawnParameters SpawnParams; 
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;



    GetWorld()->SpawnActor<AActor>(ProjectlieClass, SpawnTM, SpawnParams);

}

// Вызывается каждый кадр
void AGifCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

   
}

// Для подключения нужных функциональностей к персонажу
void AGifCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AGifCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRAL", this, &AGifCharacter::MoveRAL);

  
    PlayerInputComponent->BindAxis("Turn", this, &AGifCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("Up", this, &AGifCharacter::AddControllerPitchInput);

    PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AGifCharacter::PrimaryAttack);

}
