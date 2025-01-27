// MedievalHuntsman. Author: Olegnormchel

#include "Characters/Controllers/MHMAnimalAIController.h"
#include "Characters/Interfaces/MHMPlayerInfo.h"
#include "Characters/MHMAnimalCharacter.h"
#include "Characters/Components/AI/MHMAIComponent.h"
#include "Characters/Components/AI/MHMEscapeAIComponent.h"
#include "Characters/Components/AI/MHMPatrolAIComponent.h"
#include "Characters/Components/AI/MHMPursuitAIComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

DEFINE_LOG_CATEGORY_STATIC(LogAnimalAIController, All, All);

AMHMAnimalAIController::AMHMAnimalAIController() : Super()
{
    EscapeAIComponent = CreateDefaultSubobject<UMHMEscapeAIComponent>(TEXT("EscapeAIComponent"));
    check(EscapeAIComponent);
    EscapeAIComponent->OnEscaped.AddUObject(this, &ThisClass::OnEscaped);

    PatrolAIComponent = CreateDefaultSubobject<UMHMPatrolAIComponent>(TEXT("PatrolAIComponent"));
    check(PatrolAIComponent);

    PursuitAIComponent = CreateDefaultSubobject<UMHMPursuitAIComponent>(TEXT("PursuitComponent"));
    check(PursuitAIComponent);

    UAISenseConfig_Sight* SightSense = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightSense"));
    check(SightSense);
    SightSense->DetectionByAffiliation.bDetectNeutrals = true;

    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
    check(AIPerceptionComponent);
    AIPerceptionComponent->ConfigureSense(*SightSense);
    AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnTargetPerceptionUpdated);
}

void AMHMAnimalAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    if (IMHMAIController* AIController = Cast<IMHMAIController>(this))
    {
        AIController->SeeActor(Actor);
    }
}

void AMHMAnimalAIController::OnEscaped()
{
    StartAICompoennt(PatrolAIComponent);
}

void AMHMAnimalAIController::StartAICompoennt(UMHMAIComponent* AIComponent)
{
    check(AIComponent);
    if (CurrentAIComponent != AIComponent)
    {
        if (CurrentAIComponent)
        {
            CurrentAIComponent->Stop();
        }
        CurrentAIComponent = AIComponent;
        CurrentAIComponent->Start(this);
    }
}

void AMHMAnimalAIController::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogAnimalAIController, Warning, TEXT("BeginPlay()"));
}

void AMHMAnimalAIController::SeeActor(AActor* Actor)
{
    if (Cast<IMHMPlayerInfo>(Actor))
    {
        if (ControlledPawn->IsAgressive())
        {
            check(PursuitAIComponent);
            PursuitAIComponent->SetEnemy(Actor);
            StartAICompoennt(PursuitAIComponent);
        }
        else
        {
            check(EscapeAIComponent);
            EscapeAIComponent->SetEnemy(Actor);
            StartAICompoennt(EscapeAIComponent);
        }
    }
}

void AMHMAnimalAIController::DamageHasBeenReceived(AActor* DamageCauser)
{
    if (ControlledPawn->IsAgressive())
    {
        check(PursuitAIComponent);
        PursuitAIComponent->SetEnemy(DamageCauser);
        StartAICompoennt(PursuitAIComponent);
    }
    else
    {
        check(EscapeAIComponent);
        EscapeAIComponent->SetEnemy(DamageCauser);
        EscapeAIComponent->DamageHasBeenReceived();
        StartAICompoennt(EscapeAIComponent);
    }
}

void AMHMAnimalAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);
    check(CurrentAIComponent);
    CurrentAIComponent->OnMoveCompleted(Result.IsSuccess());
}

void AMHMAnimalAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    check(PatrolAIComponent);
    PatrolAIComponent->SetStartLocation(InPawn->GetActorLocation());
    StartAICompoennt(PatrolAIComponent);

    ControlledPawn = Cast<AMHMAnimalCharacter>(InPawn);
    if (ControlledPawn)
    {
        UE_LOG(LogAnimalAIController, Warning, TEXT("Controlled pawn initialized"));
    }
    else
    {
        UE_LOG(LogAnimalAIController, Warning, TEXT("Poshel nahui"));
    }
}
