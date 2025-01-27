// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "Characters/Interfaces/MHMStamina.h"
#include "Core/BaseTypes/MHMActorComponent.h"
#include "MHMStaminaComponent.generated.h"

UCLASS()
class MEDIEVALHUNTSMAN_API UMHMStaminaComponent final : public UMHMActorComponent, public IMHMStamina
{
    GENERATED_BODY()

public:
    UMHMStaminaComponent();

    virtual void BeginPlay() override;

    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction) override;

    virtual void UseStamina(const float UsedStamina) override;
    virtual float GetCurrentStamina() const override;
    virtual float GetPercentStamina() const override;
    virtual FOnChangedStamina& OnChangedStamina() override;
    virtual FOnRanOutStamina& OnRanOutStamina() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0"))
    float MaxStamina = 100.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0"))
    float RecoveryPerSecond = 10.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0"))
    float CurrentStamina;

    FOnChangedStamina OnChangedStaminaEvent;
    FOnRanOutStamina OnRanOutStaminaEvent;

    void SetCurrentStamina(const float InCurrentStamina);
};
