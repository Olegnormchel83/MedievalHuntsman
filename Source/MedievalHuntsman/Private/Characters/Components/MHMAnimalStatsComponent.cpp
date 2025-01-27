// MedievalHuntsman. Author: Olegnormchel

#include "Characters/Components/MHMAnimalStatsComponent.h"
#include "Characters/Components/MHMAHealthComponent.h"
#include "Core/Helpers/MHMHelperFunctions.h"

DEFINE_LOG_CATEGORY_STATIC(LogAnimalStatsComponent, All, All);

void UMHMAnimalStatsComponent::BeginPlay()
{
    Super::BeginPlay();
    Health = FMHMHelperFunctions::GetComponentByInterface<IMHMHealth>(GetOwner());
}

void UMHMAnimalStatsComponent::ApplyStats()
{
    uint32 LevelsSum = 1;
    for (uint32 i = 1; i < Level; i++)
    {
        LevelsSum += i;
    }

    FinalMaxHealth = DefaultMaxHealth + LevelsSum * ModifierHP;
    Health->SetMaxHealth(FinalMaxHealth);

    FinalDamage = DefaultDamage + (float)LevelsSum * ModifierDamage;

    FinalAttackSpeed = (DefaultAttackSpeed + (float)Level * ModifierAttackSpeed) * 0.001f + 1.0f;

    UE_LOG(LogAnimalStatsComponent, Display, TEXT("__________________________________________"));
    UE_LOG(LogAnimalStatsComponent, Display, TEXT("Animal: %s"), *GetOwner()->GetName());
    UE_LOG(LogAnimalStatsComponent, Display, TEXT("Level: %i"), Level);
    UE_LOG(LogAnimalStatsComponent, Display, TEXT("Damage: %.1f"), FinalDamage);
    UE_LOG(LogAnimalStatsComponent, Display, TEXT("AttackSpeed: %.3f"), FinalAttackSpeed);
    UE_LOG(LogAnimalStatsComponent, Display, TEXT("__________________________________________"));
}

float UMHMAnimalStatsComponent::GetAttackSpeed() const
{
    return FinalAttackSpeed;
}

float UMHMAnimalStatsComponent::GetDamage() const
{
    return FinalDamage;
}

void UMHMAnimalStatsComponent::SetAnimalLevel(uint32 InAnimalLevel)
{
    Level = InAnimalLevel;
    ApplyStats();

    UE_LOG(LogAnimalStatsComponent, Display, TEXT("SetAnimalLevel: %i"), InAnimalLevel);
}
