// MedievalHuntsman. Author: Olegnormchel

#include "Characters/MHMPlayerCharacter.h"
#include "Characters/Components/Camera/MHMCameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Core/Interfaces/MHMInteract.h"
#include "WorldObjects/InteractableObjects/Weapons/MHMWeapon.h"
#include "Characters/Components/MHMAHealthComponent.h"
#include "Characters/Components/MHMExperienceComponent.h"
#include "Characters/Components/MHMInteractComponent.h"
#include "Characters/Components/MHMStaminaComponent.h"
#include "Characters/Components/MHMPlayerStatsComponent.h"
#include "Characters/Components/MHMResurrectionComponent.h"
#include "Characters/Components/MHMWeaponComponent.h"
#include "Characters/Components/Camera/MHMCameraShakeSourceComponent.h"
#include "Characters/Interfaces/MHMMovement.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Gameframework/PlayerStart.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerCharacter, All, All)

AMHMPlayerCharacter::AMHMPlayerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
    // SpringArm
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    check(SpringArmComponent);
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->TargetArmLength = 400.0f;
    SpringArmComponent->bUsePawnControlRotation = false;

    // StaminaComponent
    StaminaComponent = CreateDefaultSubobject<UMHMStaminaComponent>(TEXT("StaminaComponent"));
    check(StaminaComponent);

    // Movement Interface
    IMHMMovement* Movement = Cast<IMHMMovement>(GetCharacterMovement());
    check(Movement);
    Movement->SetStamina(StaminaComponent);

    // CameraComponent
    CameraComponent = CreateDefaultSubobject<UMHMCameraComponent>(TEXT("CameraComponent"));
    check(CameraComponent);
    CameraComponent->SetupAttachment(SpringArmComponent);
    CameraComponent->SetStamina(StaminaComponent);

    // CameraShakeSourceComponent
    CameraShakeSourceComponent =
        CreateDefaultSubobject<UMHMCameraShakeSourceComponent>(TEXT("CameraShakeSourceComponent"));
    check(CameraShakeSourceComponent);
    CameraShakeSourceComponent->SetStamina(StaminaComponent);
    CameraShakeSourceComponent->SetupAttachment(GetRootComponent());

    // InteractTraceStartPoint
    InteractTraceStartPoint = CreateDefaultSubobject<USceneComponent>("InteractTraceStartPoint");
    check(InteractTraceStartPoint);
    InteractTraceStartPoint->SetupAttachment(GetRootComponent());

    // InteractComponent
    InteractComponent = CreateDefaultSubobject<UMHMInteractComponent>(TEXT("InteractComponent"));
    check(InteractComponent);
    InteractComponent->OnEntered.AddUObject(this, &ThisClass::OnEnteredInteractingActor);
    InteractComponent->OnLeft.AddUObject(this, &ThisClass::OnLeftInteractingActor);

    // ExperienceComponent
    ExperienceComponent = CreateDefaultSubobject<UMHMExperienceComponent>(TEXT("ExperienceComponent"));
    check(ExperienceComponent);
    ExperienceComponent->OnLevelUp.AddUObject(this, &ThisClass::OnPlayerLevelUpped);
    ExperienceComponent->OnLevelDown.AddUObject(this, &ThisClass::OnPlayerLevelReduced);

    // PlayerStatsComponent
    PlayerStatsComponent = CreateDefaultSubobject<UMHMPlayerStatsComponent>(TEXT("PlayerStatsComponent"));
    check(PlayerStatsComponent);

    // ResurrectionComponent
    ResurrectionComponent = CreateDefaultSubobject<UMHMResurrectionComponent>(TEXT("ResurrectionComponent"));
    check(ResurrectionComponent);

    // WeaponComponent
    WeaponComponent = CreateDefaultSubobject<UMHMWeaponComponent>(TEXT("WeaponComponent"));
    check(WeaponComponent);

    check(HealthComponent) HealthComponent->OnDead.AddUObject(this, &ThisClass::Dead);
}

void AMHMPlayerCharacter::OnEnteredInteractingActor(AActor* InteractingActor)
{
    if (!InteractingActor)
        return;
}

void AMHMPlayerCharacter::OnLeftInteractingActor(AActor* InteractingActor)
{
    if (!InteractingActor)
        return;
}

void AMHMPlayerCharacter::OnPlayerLevelUpped(bool bIslevelUp)
{
    UE_LOG(LogPlayerCharacter, Warning, TEXT("I am Brtue! I am LEVELUPPED!!!"));
}

void AMHMPlayerCharacter::OnPlayerLevelReduced(bool bIslevelUp)
{
    UE_LOG(LogPlayerCharacter, Warning, TEXT("I am Brtue! I miss lvl"));
}

void AMHMPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
    check(InteractComponent);
    check(GetWorld());

    InteractComponent->Start(InteractTraceStartPoint);
    CurrentCameraDistance = SpringArmComponent->TargetArmLength;

    SetLifeSpan(0.0f);
}

void AMHMPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveFB", this, &ThisClass::MoveForwardBackward);
    PlayerInputComponent->BindAxis("MoveLR", this, &ThisClass::MoveLeftRight);
    PlayerInputComponent->BindAxis("LookUD", this, &ThisClass::LookUpDown);
    PlayerInputComponent->BindAxis("LookLR", this, &ThisClass::LookLeftRight);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ThisClass::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ThisClass::StopJumping);
    PlayerInputComponent->BindAction("CameraUp", IE_Pressed, this, &ThisClass::CameraSlideUp);
    PlayerInputComponent->BindAction("CameraDown", IE_Pressed, this, &ThisClass::CameraSlideDown);
    PlayerInputComponent->BindAction("Sprinting", IE_Pressed, this, &ThisClass::StartSprinting);
    PlayerInputComponent->BindAction("Sprinting", IE_Released, this, &ThisClass::StopSprinting);
    PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ThisClass::Interact);
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &UMHMWeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("PreviousWeapon", IE_Pressed, WeaponComponent,
                                     &UMHMWeaponComponent::PreviousWeapon);
}

void AMHMPlayerCharacter::EquipWeapon(AMHMWeapon* InWeapon)
{
    if (!InWeapon)
        return;

    USkeletalMeshComponent* CharacterMesh = GetMesh();
    if (CharacterMesh)
    {
        FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
        InWeapon->AttachToComponent(CharacterMesh, AttachmentRules, FName("WeaponSocket"));
        InWeapon->SetActorHiddenInGame(false);
        InWeapon->SetOwner(this);
    }
}

void AMHMPlayerCharacter::MoveForwardBackward(const float Value)
{
    Move(EAxis::X, Value);
}

void AMHMPlayerCharacter::Move(const EAxis::Type& Axis, const float Value)
{
    if (FMath::IsNearlyZero(Value))
        return;
    if (!Controller)
        return;

    const FRotator Rotator = Controller->GetControlRotation();
    const FRotator YawRotator(0, Rotator.Yaw, 0);
    const FVector Direction = FRotationMatrix(YawRotator).GetUnitAxis(Axis);
    AddMovementInput(Direction, Value);
}

void AMHMPlayerCharacter::MoveLeftRight(const float Value)
{
    Move(EAxis::Y, Value);
    if (!CanSprinting())
    {
        SetMovementType(EMHMMovementType::Running);
    }
}

void AMHMPlayerCharacter::LookUpDown(const float Value)
{
    InteractTraceStartPoint->SetWorldRotation(CameraComponent->GetComponentRotation());
    AddControllerPitchInput(Value);
}

void AMHMPlayerCharacter::LookLeftRight(const float Value)
{
    InteractTraceStartPoint->SetWorldRotation(CameraComponent->GetComponentRotation());
    AddControllerYawInput(Value);
}

void AMHMPlayerCharacter::CameraSlideUp()
{
    CurrentCameraDistance = FMath::Max(MinCameraDistance, CurrentCameraDistance - CameraSlideStepValue);
    SpringArmComponent->TargetArmLength = CurrentCameraDistance;
}

void AMHMPlayerCharacter::CameraSlideDown()
{
    CurrentCameraDistance = FMath::Min(MaxCameraDistance, CurrentCameraDistance + CameraSlideStepValue);
    SpringArmComponent->TargetArmLength = CurrentCameraDistance;
}

void AMHMPlayerCharacter::StartSprinting()
{
    if (CanSprinting())
    {
        SetMovementType(EMHMMovementType::Sprinting);
    }
}

bool AMHMPlayerCharacter::CanSprinting() const
{
    check(GetCharacterMovement());
    const FVector MoveDirection = GetCharacterMovement()->Velocity.GetSafeNormal();
    const FVector FacingDirection = GetActorForwardVector().GetSafeNormal();

    const float DotProduct = FVector::DotProduct(MoveDirection, FacingDirection);
    const float Treshold = 0.8f;

    return DotProduct >= Treshold;
}

void AMHMPlayerCharacter::SetMovementType(const EMHMMovementType& MovementType)
{
    IMHMMovement* Movement = Cast<IMHMMovement>(GetCharacterMovement());
    check(Movement);
    Movement->SetMovementType(MovementType);
}

void AMHMPlayerCharacter::StopSprinting()
{
    SetMovementType(EMHMMovementType::Running);
}

void AMHMPlayerCharacter::Interact()
{
    check(InteractComponent);
    IMHMInteract* Interact = Cast<IMHMInteract>(InteractComponent->GetInteractingActor());
    if (Interact)
    {
        Interact->Interact(this);
    }
}

void AMHMPlayerCharacter::Dead()
{
    UE_LOG(LogPlayerCharacter, Warning, TEXT("I am Brtue! I am dead"));

    SetLifeSpan(5.0f);
}