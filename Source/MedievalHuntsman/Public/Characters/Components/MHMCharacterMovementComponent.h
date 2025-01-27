// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/Interfaces/MHMMovement.h"
#include "MHMCharacterMovementComponent.generated.h"

UCLASS()
class MEDIEVALHUNTSMAN_API UMHMCharacterMovementComponent final : public UCharacterMovementComponent,
                                                                  public IMHMMovement
{
    GENERATED_BODY()

public:
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction) override;
    virtual float GetMaxSpeed() const override;
    virtual bool DoJump(bool bReplayingMoves) override;
    virtual bool IsInAir() const override;
    virtual void SetStamina(IMHMStamina* InStamina) override;
    virtual void SetMovementType(const EMHMMovementType& InMovementType) override;
    virtual void SetCanMove() override;
    virtual void ResetCanMove() override;
    virtual bool CanMove() const override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    TMap<EMHMMovementType, float> Speeds{{EMHMMovementType::Sprinting, 900.0f},
                                         {EMHMMovementType::Running, 600.0f},
                                         {EMHMMovementType::Walking, 200.0f}};

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    TMap<EMHMMovementType, float> StaminaUsagesPerSecond{{EMHMMovementType::Sprinting, 15.0f},
                                                         {EMHMMovementType::Running, 0.0f},
                                                         {EMHMMovementType::Walking, 0.0f}};

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    float StaminaUsagePerJump = 10.0f;

    IMHMStamina* Stamina;
    EMHMMovementType MovementType = EMHMMovementType::Running;
    bool bCanMove = true;

    void RanOutStamina();
};
