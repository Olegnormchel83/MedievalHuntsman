// MedievalHuntsman. Author: Olegnormchel


#include "Characters/Components/AI/MHMEscapeAIComponent.h"
#include "Characters/Interfaces/MHMMovement.h"

DEFINE_LOG_CATEGORY_STATIC(LogEscapeAIComponent, All, All);

void UMHMEscapeAIComponent::Start(AAIController* InAIController)
{
    Super::Start(InAIController);
    SetMovementType(EMHMMovementType::Sprinting);
    GetWorldTimerManager().SetTimer(EscapeTimerHandle, this, &ThisClass::GoToNextLocation, TimerRate, true, 0.0f);
    
    UE_LOG(LogEscapeAIComponent, Warning, TEXT("EscapeAIComponent started!"));
}

void UMHMEscapeAIComponent::GoToNextLocation()
{
    check(GetControlledPawn())
    if (GetControlledPawn()->GetDistanceTo(Enemy) < GetCurrentSafeDistance())
    {
        MoveToLocation(GetNextLocation());
    }
    else
    {
        bDamageHasBeenRecieved = false;
        OnEscaped.Broadcast();
    }
}

float UMHMEscapeAIComponent::GetCurrentSafeDistance() const
{
    return bDamageHasBeenRecieved ? SafeDistanceAfterHit : SafeDistance;
}

FVector UMHMEscapeAIComponent::GetNextLocation() const
{
    check(Enemy);
    check(GetControlledPawn());
    
    FVector Delta = GetControlledPawn()->GetActorLocation() - Enemy->GetActorLocation();
    Delta.Normalize();
    const FVector Origin = GetControlledPawn()->GetActorLocation() + Delta * DistanceForEscape;

    return GetRandomPointInNavigableRadius(Origin, Radius, FColor::Green);
}

void UMHMEscapeAIComponent::Stop()
{
    Super::Stop();
    GetWorldTimerManager().ClearTimer(EscapeTimerHandle);
}

void UMHMEscapeAIComponent::SetEnemy(const AActor* InEnemy)
{
    Enemy = InEnemy;
}

void UMHMEscapeAIComponent::DamageHasBeenReceived()
{
    bDamageHasBeenRecieved = true;
}
