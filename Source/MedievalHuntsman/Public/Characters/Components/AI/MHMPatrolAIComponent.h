// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "Characters/Components/AI/MHMAIComponent.h"
#include "MHMPatrolAIComponent.generated.h"

UCLASS()
class MEDIEVALHUNTSMAN_API UMHMPatrolAIComponent final : public UMHMAIComponent
{
    GENERATED_BODY()

public:
    virtual void Start(AAIController* InAIController) override;
    virtual void Stop() override;
    virtual void OnMoveCompleted(const bool bIsSuccess) override;
    void SetStartLocation(const FVector& InStartLocation);

private:
    UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", Units = "Centimeters"))
    float Radius = 2000.0f;

    UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", Units = "Seconds"))
    float DelayAfterSuccess = 2.0f;

    UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0.2", UIMin = "0.2", Units = "Seconds"))
    float DelayAfterFail = 0.5f;

    void GoToNextLocation() const;

    FTimerHandle TimerHandle;
    FVector StartLocation;

};
