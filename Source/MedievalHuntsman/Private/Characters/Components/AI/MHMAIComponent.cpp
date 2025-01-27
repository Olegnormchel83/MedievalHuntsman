// MedievalHuntsman. Author: Olegnormchel


#include "Characters/Components/AI/MHMAIComponent.h"
#include "AIController.h"
#include "Characters/Interfaces/MHMMovement.h"
#include "Core/Helpers/MHMHelperFunctions.h"
#include "NavigationSystem.h"

void UMHMAIComponent::Start(AAIController* InAIController)
{
    AIController = InAIController;
}

void UMHMAIComponent::Stop()
{
    check(AIController);
    AIController->StopMovement();
}

void UMHMAIComponent::OnMoveCompleted(const bool bIsSuccess)
{
}

void UMHMAIComponent::SetMovementType(const EMHMMovementType& MovementType) const
{
    IMHMMovement* Movement = FMHMHelperFunctions::GetComponentByInterface<IMHMMovement>(GetControlledPawn());
    check(Movement);
    Movement->SetMovementType(MovementType);
}

void UMHMAIComponent::MoveToLocation(const FVector& Location) const
{
    check(AIController);
    AIController->MoveToLocation(Location);
}

void UMHMAIComponent::MoveToActor(AActor* Actor, float Radius) const
{
    check(AIController);
    check(Actor);
    AIController->MoveToActor(Actor, Radius, false, false, false, 0, true);
}

AActor* UMHMAIComponent::GetControlledPawn() const
{
    check(AIController);
    return AIController->GetPawn();
}

FVector UMHMAIComponent::GetRandomPointInNavigableRadius(const FVector& Origin, const float Radius,
                                                         const FColor& DebugColor) const
{
    const UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
    check(NavSys);
    FNavLocation ResultLocation;
    NavSys->GetRandomPointInNavigableRadius(Origin, Radius, ResultLocation);

    DrawDebugSphere(GetWorld(), ResultLocation.Location, 100, 10, FColor::Green, false, 10.0f);

    return ResultLocation.Location;
}
