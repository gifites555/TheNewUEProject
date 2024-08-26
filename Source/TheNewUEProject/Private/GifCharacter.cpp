#include "GifCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AGifCharacter::AGifCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

// Called when the game starts or when spawned
void AGifCharacter::BeginPlay()
{
    Super::BeginPlay();
}

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
    PlayerInputComponent->BindAxis("MoveRAL", this, &AGifCharacter::MoveRAL);

  
    PlayerInputComponent->BindAxis("Turn", this, &AGifCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("Up", this, &AGifCharacter::AddControllerPitchInput);
}
