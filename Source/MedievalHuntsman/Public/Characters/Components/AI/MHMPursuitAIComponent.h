// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "Characters/Components/AI/MHMAIComponent.h"
#include "Characters/Interfaces/MHMAnimalStats.h"
#include "MHMPursuitAIComponent.generated.h"

class AMHMAnimalCharacter;

UCLASS()
class MEDIEVALHUNTSMAN_API UMHMPursuitAIComponent : public UMHMAIComponent
{
    GENERATED_BODY()

public:
    virtual void Start(AAIController* InAIController) override;
    virtual void Stop() override;
    void SetEnemy(AActor* InEnemy);

private:
    UPROPERTY()
    AActor* Enemy;

    UPROPERTY()
    const AMHMAnimalCharacter* ControlledPawn;

    UPROPERTY(EditDefaultsOnly, Category = "Settings",
              meta = (ClampMin = "200.0", UIMin = "200.0", Units = "Centimeters"))
    float AttackRange = 400.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Settings",
              meta = (ClampMin = "0.1", UIMin = "0.1", Units = "Seconds"))
    float PursuitTimerRate = 1.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Animations")
    UAnimMontage* AttackAnimMontage;

    float AttackSpeed = 0.0f;
    float Damage = 0.0f;

    IMHMAnimalStats* AnimalStats;

    FTimerHandle PursuitTimerHandle;
    FTimerHandle AttackTimerHandle;

    void Pursuit();
    void StartAttack();
    void Attack();
    void SmoothRotationToTarget();
    void StrictRotationToTarget();
    float GetCurrentDistanceToEnemy() const;
};
