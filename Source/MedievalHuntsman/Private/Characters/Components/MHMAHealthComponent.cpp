// MedievalHuntsman. Author: Olegnormchel

#include "Characters/Components/MHMAHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

void UMHMAHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    SetCurrentHealth(MaxHealth);
    bIsDead = false;

    //UE_LOG(LogHealthComponent, Display, TEXT("UMHMAHealthComponent::BeginPlay()"));
}

void UMHMAHealthComponent::SetCurrentHealth(const float InCurrenthealth)
{
    if (bIsDead)
        return;

    CurrentHealth = FMath::Clamp(InCurrenthealth, 0, MaxHealth);
    if (FMath::IsNearlyZero(CurrentHealth))
    {
        bIsDead = true;
        OnDead.Broadcast();
        //UE_LOG(LogHealthComponent, Warning, TEXT("OnDead.Broadcast()"));
    }

    if (FMath::IsNearlyEqual(CurrentHealth, MaxHealth))
    {
        GetWorldTimerManager().ClearTimer(RegenerationTimerHandle);
        //UE_LOG(LogHealthComponent, Warning, TEXT("Regeneration deactivated"));
    }
}

void UMHMAHealthComponent::AddHealth(const float AddValue)
{
    SetCurrentHealth(CurrentHealth + AddValue);

   //UE_LOG(LogHealthComponent, Warning, TEXT("%s regen %f health"), *GetOwner()->GetName(), AddValue);
}

void UMHMAHealthComponent::ReduceHealth(const float ReduceValue)
{
    GetWorldTimerManager().ClearTimer(RegenerationTimerHandle);
    SetCurrentHealth(CurrentHealth - ReduceValue);

    
    //UE_LOG(LogHealthComponent, Warning, TEXT("Regeneration deactivated"));
    //UE_LOG(LogHealthComponent, Warning, TEXT("%s get %f damage"), *GetOwner()->GetName(), ReduceValue);
    

    
    GetWorldTimerManager().SetTimer(NoDamageTimerHandle, this, &ThisClass::Regeneration, SecondsNeedToStartRegeneration, false);
}

void UMHMAHealthComponent::Regeneration()
{
    GetWorldTimerManager().SetTimer(RegenerationTimerHandle, this, &ThisClass::RegenerationTick, 1.0f, true, 0.0f);
    //UE_LOG(LogHealthComponent, Warning, TEXT("Regeneration activated"));
}

void UMHMAHealthComponent::RegenerationTick()
{
    AddHealth(RegenHealthPerSecond);
}

float UMHMAHealthComponent::GetMaxHealth() const
{
    return MaxHealth;
}

void UMHMAHealthComponent::SetMaxHealth(const float InMaxHealth)
{
    MaxHealth = InMaxHealth;
}

float UMHMAHealthComponent::GetRegenHealthPerSecond() const
{
    return RegenHealthPerSecond;
}

void UMHMAHealthComponent::SetRegenHealthPerSecond(const float InRegenHealthValue)
{
    RegenHealthPerSecond = InRegenHealthValue;
}
