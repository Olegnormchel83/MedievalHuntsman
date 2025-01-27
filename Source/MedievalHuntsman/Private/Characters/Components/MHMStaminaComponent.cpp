// MedievalHuntsman. Author: Olegnormchel

#include "Characters/Components/MHMStaminaComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogStaminaComponent, All, All);

UMHMStaminaComponent::UMHMStaminaComponent() : Super()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UMHMStaminaComponent::BeginPlay()
{
    Super::BeginPlay();
    SetCurrentStamina(MaxStamina);
}

void UMHMStaminaComponent::SetCurrentStamina(const float InCurrentStamina)
{
    CurrentStamina = FMath::Clamp(InCurrentStamina, 0.0f, MaxStamina);
    OnChangedStaminaEvent.Broadcast();
    if (FMath::IsNearlyZero(CurrentStamina))
    {
        OnRanOutStaminaEvent.Broadcast();
    }
}

void UMHMStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    SetCurrentStamina(CurrentStamina + DeltaTime * RecoveryPerSecond);
}


void UMHMStaminaComponent::UseStamina(const float UsedStamina)
{
    SetCurrentStamina(CurrentStamina - UsedStamina);
}

float UMHMStaminaComponent::GetCurrentStamina() const
{
    return CurrentStamina;
}

float UMHMStaminaComponent::GetPercentStamina() const
{
    if (FMath::IsNearlyZero(MaxStamina))
        return 0.0f;
    return CurrentStamina / MaxStamina;
}

FOnChangedStamina& UMHMStaminaComponent::OnChangedStamina()
{
    return OnChangedStaminaEvent;
}

FOnRanOutStamina& UMHMStaminaComponent::OnRanOutStamina()
{
    return OnRanOutStaminaEvent;
}
