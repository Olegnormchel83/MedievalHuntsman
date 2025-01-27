// MedievalHuntsman. Author: Olegnormchel

#include "Characters/Components/MHMCharacterMovementComponent.h"
#include "Characters/Interfaces/MHMStamina.h"

void UMHMCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                   FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if (!Stamina)
        return;

    check(StaminaUsagesPerSecond.Contains(MovementType));
    check(GetOwner());

    const float OwnerVelocity = GetOwner()->GetVelocity().Length();
    if (!FMath::IsNearlyZero(OwnerVelocity))
    {
        Stamina->UseStamina(StaminaUsagesPerSecond[MovementType] * DeltaTime);
    }
}

float UMHMCharacterMovementComponent::GetMaxSpeed() const
{
    check(Speeds.Contains(MovementType));
    return Speeds[MovementType];
}

bool UMHMCharacterMovementComponent::DoJump(bool bReplayingMoves)
{
    if (!Stamina)
    {
        return Super::DoJump(bReplayingMoves);
    }

    if (Stamina->GetCurrentStamina() > StaminaUsagePerJump)
    {
        Stamina->UseStamina(StaminaUsagePerJump);
        return Super::DoJump(bReplayingMoves);
    }
    return false;
}

bool UMHMCharacterMovementComponent::IsInAir() const
{
    return IsFalling();
}

void UMHMCharacterMovementComponent::SetStamina(IMHMStamina* InStamina)
{
    Stamina = InStamina;
    check(Stamina);
    Stamina->OnRanOutStamina().AddUObject(this, &ThisClass::RanOutStamina);
}

void UMHMCharacterMovementComponent::RanOutStamina()
{
    for (const TPair<EMHMMovementType, float>& Pair : StaminaUsagesPerSecond)
    {
        if (FMath::IsNearlyZero(Pair.Value))
        {
            SetMovementType(Pair.Key);
            return;
        }
    }
    StopMovementImmediately();
}

void UMHMCharacterMovementComponent::SetMovementType(const EMHMMovementType& InMovementType)
{
    MovementType = InMovementType;
}

void UMHMCharacterMovementComponent::SetCanMove()
{
    bCanMove = true;
}

void UMHMCharacterMovementComponent::ResetCanMove()
{
    bCanMove = false;
}

bool UMHMCharacterMovementComponent::CanMove() const
{
    return bCanMove;
}
