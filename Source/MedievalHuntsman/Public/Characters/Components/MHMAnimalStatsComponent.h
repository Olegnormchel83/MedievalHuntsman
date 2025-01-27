// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "Core/BaseTypes/MHMActorComponent.h"
#include "Characters/Interfaces/MHMHealth.h"
#include "Characters/Interfaces/MHMAnimalStats.h"
#include "MHMAnimalStatsComponent.generated.h"

UCLASS()
class MEDIEVALHUNTSMAN_API UMHMAnimalStatsComponent : public UMHMActorComponent, public IMHMAnimalStats
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;
    virtual float GetAttackSpeed() const override;
    virtual float GetDamage() const override;
    virtual void SetAnimalLevel(uint32 InAnimalLevel) override;

private:
    UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "1", UIMin = "1"))
    uint32 Level = 1;

    // Modifiers
    UPROPERTY(EditAnywhere, Category = "Settings|Modifiers", meta = (ClampMin = "1", UIMin = "1"))
    float ModifierHP = 100.0f;

    UPROPERTY(EditAnywhere, Category = "Settings|Modifiers", meta = (ClampMin = "1", UIMin = "1"))
    float ModifierDamage = 13.0f;

    UPROPERTY(EditAnywhere, Category = "Settings|Modifiers", meta = (ClampMin = "1", UIMin = "1"))
    float ModifierAttackSpeed = 20.0f;

    // Default Values
    UPROPERTY(EditAnywhere, Category = "Settings|Default", meta = (ClampMin = "1", UIMin = "1"))
    float DefaultMaxHealth = 50.0f;

    UPROPERTY(EditAnywhere, Category = "Settings|Default", meta = (ClampMin = "1", UIMin = "1"))
    float DefaultDamage = 10.0f;

    UPROPERTY(EditAnywhere, Category = "Settings|Default", meta = (ClampMin = "1", UIMin = "1"))
    float DefaultAttackSpeed = 1.0f;

    // Final Values
    UPROPERTY(VisibleAnywhere, Category = "Settings|Final")
    float FinalMaxHealth;

    UPROPERTY(VisibleAnywhere, Category = "Settings|Final")
    float FinalDamage;

    UPROPERTY(VisibleAnywhere, Category = "Settings|Final")
    float FinalAttackSpeed;

    IMHMHealth* Health;

    void ApplyStats();
};
