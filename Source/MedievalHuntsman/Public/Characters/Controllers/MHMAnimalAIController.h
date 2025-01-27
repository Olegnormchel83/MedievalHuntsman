// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Characters/Interfaces/MHMAIController.h"
#include "MHMAnimalAIController.generated.h"

class UAIPerceptionComponent;
class AMHMAnimalCharacter;
class UMHMAIComponent;
class UMHMEscapeAIComponent;
class UMHMPatrolAIComponent;
class UMHMPursuitAIComponent;

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API AMHMAnimalAIController final : public AAIController, public IMHMAIController
{
    GENERATED_BODY()

public:
    AMHMAnimalAIController();

    virtual void BeginPlay() override;

    virtual void SeeActor(AActor* Actor) override;
    virtual void DamageHasBeenReceived(AActor* DamageCauser) override;
    virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

protected:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UAIPerceptionComponent* AIPerceptionComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Components")
    UMHMPatrolAIComponent* PatrolAIComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Components")
    UMHMEscapeAIComponent* EscapeAIComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Components")
    UMHMPursuitAIComponent* PursuitAIComponent;

    virtual void OnPossess(APawn* InPawn) override;

private:
    UPROPERTY()
    AMHMAnimalCharacter* ControlledPawn;

    UPROPERTY()
    UMHMAIComponent* CurrentAIComponent;

    UFUNCTION()
    void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

    void OnEscaped();
    void StartAICompoennt(UMHMAIComponent* AIComponent);
};
