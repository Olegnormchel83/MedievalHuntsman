// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "Core/BaseTypes/MHMActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MHMInteractComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEntered, AActor*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnLeft, AActor*);

UCLASS()
class MEDIEVALHUNTSMAN_API UMHMInteractComponent final : public UMHMActorComponent
{
    GENERATED_BODY()

public:
    FOnEntered OnEntered;
    FOnLeft OnLeft;

    void Start(USceneComponent* InSceneComponent);

    AActor* GetInteractingActor() const;

private:
    FTimerHandle TimerHandle;

    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", Units = "Seconds"))
    float TimerTickRate = 0.1f;

    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", Units = "Centimeters"))
    float Radius = 40.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", Units = "Centimeters"))
    float Distance = 200.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    TEnumAsByte<ETraceTypeQuery> TraceTypeQuery;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType;

    UPROPERTY()
    USceneComponent* SceneComponent;

    UPROPERTY()
    AActor* InteractingActor;

    void InteractTick();

};
