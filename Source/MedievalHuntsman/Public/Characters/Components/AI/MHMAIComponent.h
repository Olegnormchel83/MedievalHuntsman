// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "Core/BaseTypes/MHMActorComponent.h"
#include "MHMAIComponent.generated.h"

enum class EMHMMovementType : uint8;
class AAIController;

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API UMHMAIComponent : public UMHMActorComponent
{
    GENERATED_BODY()

public:
    virtual void Start(AAIController* InAIController);
    virtual void Stop();
    virtual void OnMoveCompleted(const bool bIsSuccess);

protected:
    void SetMovementType(const EMHMMovementType& MovementType) const;
    void MoveToLocation(const FVector& Location) const;
    void MoveToActor(AActor* Actor, float Radius) const;
    AActor* GetControlledPawn() const;
    FVector GetRandomPointInNavigableRadius(const FVector& Origin, const float Radius, const FColor& DebugColor) const;

private:
    UPROPERTY()
    AAIController* AIController;
};
