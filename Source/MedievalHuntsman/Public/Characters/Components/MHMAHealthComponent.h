// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "Core/BaseTypes/MHMActorComponent.h"
#include "Characters/Interfaces/MHMHealth.h"
#include "MHMAHealthComponent.generated.h"

UCLASS()
class MEDIEVALHUNTSMAN_API UMHMAHealthComponent final : public UMHMActorComponent, public IMHMHealth
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

    virtual void SetCurrentHealth(const float InCurrentHealth) override;

    UFUNCTION(BlueprintCallable)
    virtual void AddHealth(const float AddValue) override;

    UFUNCTION(BlueprintCallable)
    virtual void ReduceHealth(const float ReduceValue) override;

    virtual void Regeneration() override;
    virtual void RegenerationTick() override;

    virtual float GetMaxHealth() const override;
    virtual void SetMaxHealth(const float InMaxHealth) override;
    virtual float GetRegenHealthPerSecond() const override;
    virtual void SetRegenHealthPerSecond(const float InRegenHealthValue) override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0"))
    float MaxHealth = 100.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Settings|Regeneration",
              meta = (ClampMin = "1", UIMin = "1", ClampMax = "15", UIMax = "15"))
    float RegenHealthPerSecond;

    UPROPERTY(EditDefaultsOnly, Category = "Settings|Regeneration", meta = (ClampMin = "1", UIMin = "1"))
    float SecondsNeedToStartRegeneration = 5.0f;

    FTimerHandle RegenerationTimerHandle;
    FTimerHandle NoDamageTimerHandle;

    float CurrentHealth;
    bool bIsDead = false;
};
