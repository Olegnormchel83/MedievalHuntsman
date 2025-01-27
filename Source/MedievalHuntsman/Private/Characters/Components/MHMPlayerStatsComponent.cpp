// MedievalHuntsman. Author: Olegnormchel

#include "Characters/Components/MHMPlayerStatsComponent.h"
#include "Core/Helpers/MHMHelperFunctions.h"
#include "Characters/Components/MHMExperienceComponent.h"
#include "Characters/Components/MHMAHealthComponent.h"
#include "Characters/MHMPlayerCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerStatsComponent, All, All);

void UMHMPlayerStatsComponent::BeginPlay()
{
    Super::BeginPlay();

    Actor = GetOwner();
    Experience = FMHMHelperFunctions::GetComponentByInterface<IMHMExperience>(Actor);
    Experience->OnLevelUp.AddUObject(this, &ThisClass::ApplyModifiers);
    Experience->OnLevelDown.AddUObject(this, &ThisClass::ApplyModifiers);
    Health = FMHMHelperFunctions::GetComponentByInterface<IMHMHealth>(Actor);
}

void UMHMPlayerStatsComponent::ApplyModifiers(bool bisLevelUp)
{
    if (!Actor)
        return;

    PlayerLevel = Experience->GetCurrentLevel();
    UE_LOG(LogPlayerStatsComponent, Warning, TEXT("PlayerLevel: %i"), PlayerLevel);
    PlayerHealth = Health->GetMaxHealth();
    PlayerRegen = Health->GetRegenHealthPerSecond();

    float NewPlayerMaxHealth;
    float NewPlayerRegenHealthPerSecond;
    if (bisLevelUp)
    {
        NewPlayerMaxHealth = PlayerHealth + PlayerLevel * MaxHealthModifier;
        NewPlayerRegenHealthPerSecond = PlayerRegen + PlayerLevel * HealthRegenerationModifier;

        UE_LOG(LogPlayerStatsComponent, Warning, TEXT("Level Up!"));
        UE_LOG(LogPlayerStatsComponent, Warning, TEXT("Max health increased to %f"), NewPlayerMaxHealth);
        UE_LOG(LogPlayerStatsComponent, Warning, TEXT("Health regeneration increased to %f"),
               NewPlayerRegenHealthPerSecond);
    }
    else
    {
        NewPlayerMaxHealth = PlayerHealth - PlayerLevel * MaxHealthModifier;
        NewPlayerRegenHealthPerSecond = PlayerRegen - PlayerLevel * HealthRegenerationModifier;

        UE_LOG(LogPlayerStatsComponent, Warning, TEXT("Level Down!"));
        UE_LOG(LogPlayerStatsComponent, Warning, TEXT("Max health reduced to %f"), NewPlayerMaxHealth);
        UE_LOG(LogPlayerStatsComponent, Warning, TEXT("Health regeneration reduced to %f"),
               NewPlayerRegenHealthPerSecond);
    }

    Health->SetMaxHealth(NewPlayerMaxHealth);
    Health->SetRegenHealthPerSecond(NewPlayerRegenHealthPerSecond);

}
