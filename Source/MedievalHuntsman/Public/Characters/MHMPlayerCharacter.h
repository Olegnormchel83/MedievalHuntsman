// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "Characters/MHMCharacter.h"
#include "Characters/Interfaces/MHMMovement.h"
#include "Characters/Interfaces/MHMPlayerInfo.h"
#include "MHMPlayerCharacter.generated.h"

class UMHMCameraComponent;
class UMHMCameraShakeSourceComponent;
class UMHMExperienceComponent;
class UMHMInteractComponent;
class UMHMPlayerStatsComponent;
class UMHMResurrectionComponent;
class UMHMStaminaComponent;
class UMHMWeaponComponent;
class USpringArmComponent;

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API AMHMPlayerCharacter final : public AMHMCharacter, public IMHMPlayerInfo
{
    GENERATED_BODY()

public:
    explicit AMHMPlayerCharacter(const FObjectInitializer& ObjInit);

    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void EquipWeapon(AMHMWeapon* InWeapon) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UMHMCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USceneComponent* InteractTraceStartPoint;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UMHMInteractComponent* InteractComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UMHMCameraShakeSourceComponent* CameraShakeSourceComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UMHMExperienceComponent* ExperienceComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UMHMStaminaComponent* StaminaComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UMHMResurrectionComponent* ResurrectionComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UMHMPlayerStatsComponent* PlayerStatsComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UMHMWeaponComponent* WeaponComponent;

    virtual void BeginPlay() override;

private:
    void MoveForwardBackward(const float Value);
    void MoveLeftRight(const float Value);
    void Move(const EAxis::Type& Axis, const float Value);
    void LookUpDown(const float Value);
    void LookLeftRight(const float Value);
    void CameraSlideUp();
    void CameraSlideDown();
    void StartSprinting();
    void StopSprinting();
    void Interact();
    void SetMovementType(const EMHMMovementType& MovementType);
    bool CanSprinting() const;

    void OnEnteredInteractingActor(AActor* InteractingActor);
    void OnLeftInteractingActor(AActor* InteractingActor);

    void OnPlayerLevelUpped(bool bIslevelUp);
    void OnPlayerLevelReduced(bool bIslevelUp);

    void Dead();

    UPROPERTY(EditDefaultsOnly, Category = "CameraSettings")
    float CurrentCameraDistance;

    UPROPERTY(EditDefaultsOnly, Category = "CameraSettings")
    float MinCameraDistance = 300.0f;

    UPROPERTY(EditDefaultsOnly, Category = "CameraSettings")
    float MaxCameraDistance = 900.0f;

    UPROPERTY(EditDefaultsOnly, Category = "CameraSettings")
    float CameraSlideStepValue = 30.0f;

    bool bCanSprinting = true;
    FVector ResurrectionLocation;
};