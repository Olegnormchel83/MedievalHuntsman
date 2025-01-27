// MedievalHuntsman. Author: Olegnormchel

#include "Characters/Animations/MHMPawnAnimInstance.h"
#include "KismetAnimationLibrary.h"
#include "Core/Helpers/MHMHelperFunctions.h"

DEFINE_LOG_CATEGORY_STATIC(LogPawnAnimInstance, All, All);

void UMHMPawnAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
    Pawn = TryGetPawnOwner();
    Movement = FMHMHelperFunctions::GetComponentByInterface<IMHMMovement>(Pawn);
}

void UMHMPawnAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    if (Pawn)
    {
        Speed = Pawn->GetVelocity().Size();
        Direction = UKismetAnimationLibrary::CalculateDirection(Pawn->GetVelocity(), Pawn->GetActorRotation());
        TurnAngle = CalculateAngleBetweenDirections();
        bHasTurnAngle = !FMath::IsNearlyZero(FMath::Abs(TurnAngle));
        if (Movement)
        {
            bIsFalling = Movement->IsInAir();
        }
    }
}

float UMHMPawnAnimInstance::CalculateAngleBetweenDirections()
{
    if (!Pawn)
        return 0.0f;

    FVector Velocity = Pawn->GetVelocity();
    if (Pawn->GetVelocity().IsNearlyZero())
        return 0.0f;

    FVector ForwardVector = Pawn->GetActorForwardVector();

    ForwardVector.Normalize();
    Velocity.Normalize();

    float DotProduct = FVector::DotProduct(ForwardVector, Velocity);
    float AngleInRadians = FMath::Acos(DotProduct);

    float AngleInDegrees = FMath::RadiansToDegrees(AngleInRadians);

    FVector CrossProduct = FVector::CrossProduct(ForwardVector, Velocity);
    if (CrossProduct.Z < 0)
    {
        AngleInDegrees = -AngleInDegrees;
    }

    return AngleInDegrees;
}
