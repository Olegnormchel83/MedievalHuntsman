// MedievalHuntsman. Author: Olegnormchel

#include "Characters/Components/AI/MHMPursuitAIComponent.h"
#include "Characters/Components/MHMAnimalStatsComponent.h"
#include "Characters/Interfaces/MHMMovement.h"
#include "Characters/MHMAnimalCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Core/Helpers/MHMHelperFunctions.h"

DEFINE_LOG_CATEGORY_STATIC(LogPusruitAIComponent, All, All);

void UMHMPursuitAIComponent::Start(AAIController* InAIController)
{
    Super::Start(InAIController);
    SetMovementType(EMHMMovementType::Sprinting);
    GetWorldTimerManager().SetTimer(PursuitTimerHandle, this, &ThisClass::Pursuit, PursuitTimerRate, true, 0.0f);

    ControlledPawn = Cast<AMHMAnimalCharacter>(GetControlledPawn());
    check(ControlledPawn);

    AnimalStats = FMHMHelperFunctions::GetComponentByInterface<IMHMAnimalStats>(ControlledPawn);
    check(AnimalStats);
    AttackSpeed = AnimalStats->GetAttackSpeed();
    Damage = AnimalStats->GetDamage();

    AttackAnimMontage->RateScale = AttackSpeed;

    UE_LOG(LogPusruitAIComponent, Warning, TEXT("PursuitAIComponent started"));
}

void UMHMPursuitAIComponent::Pursuit()
{
    if (GetCurrentDistanceToEnemy() > AttackRange)
    {
        MoveToActor(Enemy, AttackRange);
    }
    else
    {
        StartAttack();
    }
}

void UMHMPursuitAIComponent::StartAttack()
{
    GetWorldTimerManager().ClearTimer(PursuitTimerHandle);
    GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &ThisClass::Attack, 1.0f / AttackSpeed, true, 0.0f);
}

void UMHMPursuitAIComponent::Attack()
{
    StrictRotationToTarget();
    //SmoothRotationToTarget();
    if (GetCurrentDistanceToEnemy() <= AttackRange)
    {
        if (AttackAnimMontage)
        {
            // AttackLogic
            ControlledPawn->GetMesh()->PlayAnimation(AttackAnimMontage, false);
        }
        // Logs
    }
    else
    {
        ControlledPawn->GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint, true);
        MoveToActor(Enemy, AttackRange * 0.8f);
    }
}

void UMHMPursuitAIComponent::SmoothRotationToTarget()
{
    check(GetWorld());
    check(GetControlledPawn());
    check(Enemy);

    FRotator CurrentRotation = GetControlledPawn()->GetActorRotation();
    FRotator TargetRotation =
        UKismetMathLibrary::FindLookAtRotation(GetControlledPawn()->GetActorLocation(), Enemy->GetActorLocation());
    float DeltaTime = GetWorld()->GetDeltaSeconds();
    float RotationSpeed = 0.3f;

    FRotator SmoothRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, RotationSpeed);
    GetControlledPawn()->SetActorRotation(SmoothRotation);
}

void UMHMPursuitAIComponent::StrictRotationToTarget()
{
    check(GetControlledPawn());
    check(Enemy);

    GetControlledPawn()->SetActorRotation(
        UKismetMathLibrary::FindLookAtRotation(GetControlledPawn()->GetActorLocation(), Enemy->GetActorLocation()));
}

float UMHMPursuitAIComponent::GetCurrentDistanceToEnemy() const
{
    check(GetControlledPawn());
    return GetControlledPawn()->GetDistanceTo(Enemy);
}

void UMHMPursuitAIComponent::Stop()
{
    Super::Stop();
    GetWorldTimerManager().ClearTimer(AttackTimerHandle);
}

void UMHMPursuitAIComponent::SetEnemy(AActor* InEnemy)
{
    Enemy = InEnemy;
}