// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "Core/BaseTypes/MHMActorComponent.h"
#include "Characters/Interfaces/MHMExperience.h"
#include "Characters/Interfaces/MHMHealth.h"
#include "MHMPlayerStatsComponent.generated.h"

UCLASS()
class MEDIEVALHUNTSMAN_API UMHMPlayerStatsComponent final : public UMHMActorComponent
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "PlayerStatsModifiers|Combat", meta = (ClampMin = "1", UIMin = "1"))
    float AttackPowerModifier;

    UPROPERTY(EditDefaultsOnly, Category = "PlayerStatsModifiers|Combat", meta = (ClampMin = "1", UIMin = "1"))
    float AttackSpeedModifier;

    UPROPERTY(EditDefaultsOnly, Category = "PlayerStatsModifiers|Health", meta = (ClampMin = "1", UIMin = "1"))
    float MaxHealthModifier = 50.0f;

    UPROPERTY(EditDefaultsOnly, Category = "PlayerStatsModifiers|Health", meta = (ClampMin = "1", UIMin = "1"))
    float HealthRegenerationModifier = 1.5f;

    UPROPERTY()
    AActor* Actor;

    IMHMExperience* Experience;
    IMHMHealth* Health;

    int32 PlayerLevel;
    float PlayerHealth;
    float PlayerRegen;

    void ApplyModifiers(bool bIsLevelUp);

};
