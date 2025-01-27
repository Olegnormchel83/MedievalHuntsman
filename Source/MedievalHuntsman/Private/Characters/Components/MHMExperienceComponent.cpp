// MedievalHuntsman. Author: Olegnormchel

#include "Characters/Components/MHMExperienceComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogExperienceComponent, All, All);

void UMHMExperienceComponent::BeginPlay()
{
    Super::BeginPlay();
    ExperienceForNextLevel = CalculateExperienceForNextLevel(CurrentLevel);
}

int32 UMHMExperienceComponent::CalculateExperienceForNextLevel(const int32 InLevel)
{
    if (InLevel == 1)
        return ExpForLevelTwo;

    int32 Sum = 0;
    for (int i = 1; i <= InLevel; i++)
    {
        Sum += i;
    }

    UE_LOG(LogExperienceComponent, Warning, TEXT("Exp for next Lvl: %i"), ExpForLevelTwo * Sum);
    return ExpForLevelTwo * Sum;
}

void UMHMExperienceComponent::AddExperience(const int32 AddValue)
{
    int32 NextExperienceValue = CurrentExperience + AddValue;

    if (NextExperienceValue >= ExperienceForNextLevel)
    {
        ++CurrentLevel;
        OnLevelUp.Broadcast(true);
        CurrentExperience = NextExperienceValue - ExperienceForNextLevel;
        ExperienceForNextLevel = CalculateExperienceForNextLevel(CurrentLevel);
    }
    else
    {
        CurrentExperience = NextExperienceValue;
    }

    UE_LOG(LogExperienceComponent, Warning, TEXT("Exp gained: %i"), AddValue);
}

void UMHMExperienceComponent::ReduceExperience(const int32 ReduceValue)
{
    if (CurrentLevel == 1)
        return;

    int32 NextExperienceValue = CurrentExperience - ReduceValue;

    if (NextExperienceValue < 0)
    {
        --CurrentLevel;
        int32 Remains = -NextExperienceValue;
        OnLevelDown.Broadcast(false);
        CurrentExperience = CalculateExperienceForNextLevel(CurrentLevel) - Remains;
        ExperienceForNextLevel = CalculateExperienceForNextLevel(CurrentLevel);
    }
    else
    {
        CurrentExperience = NextExperienceValue;
    }

    UE_LOG(LogExperienceComponent, Warning, TEXT("Exp lose: %i"), ReduceValue);
}

int32 UMHMExperienceComponent::GetCurrentLevel() const
{
    return CurrentLevel;
}
