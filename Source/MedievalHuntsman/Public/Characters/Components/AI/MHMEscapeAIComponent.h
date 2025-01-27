// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "Characters/Components/AI/MHMAIComponent.h"
#include "MHMEscapeAIComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnEscaped);

UCLASS()
class MEDIEVALHUNTSMAN_API UMHMEscapeAIComponent final : public UMHMAIComponent
{
    GENERATED_BODY()

public:
    FOnEscaped OnEscaped;

    virtual void Start(AAIController* InAIController) override;
    virtual void Stop() override;
    void SetEnemy(const AActor* InEnemy);
    void DamageHasBeenReceived();

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", Units = "Centimeters"))
    float SafeDistance = 3000.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", Units = "Centimeters"))
    float SafeDistanceAfterHit = 10000.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", Units = "Centimeters"))
    float DistanceForEscape = 1000.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", Units = "Centimeters"))
    float Radius = 100.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0.1", UIMin = "0.1", Units = "Seconds"))
    float TimerRate = 0.5f;

    UPROPERTY()
    const AActor* Enemy;

    FTimerHandle EscapeTimerHandle;
    bool bDamageHasBeenRecieved = false;

    void GoToNextLocation();
    float GetCurrentSafeDistance() const;
    FVector GetNextLocation() const;
};
