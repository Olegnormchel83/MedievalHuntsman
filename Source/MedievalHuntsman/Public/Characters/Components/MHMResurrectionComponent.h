// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "Core/BaseTypes/MHMActorComponent.h"
#include "Characters/Interfaces/MHMHealth.h"
#include "MHMResurrectionComponent.generated.h"

UCLASS()
class MEDIEVALHUNTSMAN_API UMHMResurrectionComponent : public UMHMActorComponent
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "3", UIMin = "3"))
    float ResurrectionTime = 5.0f;

    FTimerHandle ResurrectionTimerHandle;
    IMHMHealth* Health;
    AActor* Owner;

    void OnDeath();
    void ResurrectCharacter();
};
