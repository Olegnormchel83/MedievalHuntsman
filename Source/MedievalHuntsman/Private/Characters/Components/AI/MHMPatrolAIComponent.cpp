// MedievalHuntsman. Author: Olegnormchel

#include "Characters/Components/AI/MHMPatrolAIComponent.h"
#include "Characters/Interfaces/MHMMovement.h"
#include "AIController.h"
#include "NavigationSystem.h"

DEFINE_LOG_CATEGORY_STATIC(LogPatrolAIComponent, All, All);

void UMHMPatrolAIComponent::Start(AAIController* InAIController)
{
    Super::Start(InAIController);
    SetMovementType(EMHMMovementType::Walking);
    GetWorldTimerManager().SetTimer(TimerHandle, this, &ThisClass::GoToNextLocation, DelayAfterSuccess);
}

void UMHMPatrolAIComponent::GoToNextLocation() const
{
    MoveToLocation(GetRandomPointInNavigableRadius(StartLocation, Radius, FColor::Red));
}

void UMHMPatrolAIComponent::Stop()
{
    Super::Stop();
    GetWorldTimerManager().ClearTimer(TimerHandle);

    UE_LOG(LogPatrolAIComponent, Warning, TEXT("PatrolAIComponent stopped!"));
}

void UMHMPatrolAIComponent::OnMoveCompleted(const bool bIsSuccess)
{
    Super::OnMoveCompleted(bIsSuccess);

    const float RealDelay = bIsSuccess ? DelayAfterSuccess : DelayAfterFail;
    GetWorldTimerManager().SetTimer(TimerHandle, this, &ThisClass::GoToNextLocation, RealDelay);
}

void UMHMPatrolAIComponent::SetStartLocation(const FVector& InStartLocation)
{
    StartLocation = InStartLocation;
}