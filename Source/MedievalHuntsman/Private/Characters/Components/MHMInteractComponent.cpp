// MedievalHuntsman. Author: Olegnormchel

#include "Characters/Components/MHMInteractComponent.h"

void UMHMInteractComponent::Start(USceneComponent* InSceneComponent)
{
    SceneComponent = InSceneComponent;
    GetWorldTimerManager().SetTimer(TimerHandle, this, &ThisClass::InteractTick, TimerTickRate, true);
}

void UMHMInteractComponent::InteractTick()
{
    check(SceneComponent);
    const FVector StartLocation = SceneComponent->GetComponentLocation();
    const FVector EndLocation = StartLocation + SceneComponent->GetForwardVector() * Distance;
    FHitResult OutHit;
    TArray<AActor*> IgnoredActors;
    IgnoredActors.Add(GetOwner());
    UKismetSystemLibrary::SphereTraceSingle(this, StartLocation, EndLocation, Radius, TraceTypeQuery, false,
                                            IgnoredActors, DrawDebugType, OutHit, true);

    if (OutHit.GetActor() != InteractingActor)
    {
        OnLeft.Broadcast(InteractingActor);
        InteractingActor = OutHit.GetActor();
        OnEntered.Broadcast(InteractingActor);
    }
}

AActor* UMHMInteractComponent::GetInteractingActor() const
{
    return InteractingActor;
}