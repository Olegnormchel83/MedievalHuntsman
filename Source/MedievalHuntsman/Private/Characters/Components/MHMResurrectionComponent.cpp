// MedievalHuntsman. Author: Olegnormchel

#include "Characters/Components/MHMResurrectionComponent.h"
#include "Characters/MHMPlayerCharacter.h"
#include "Characters/MHMAnimalCharacter.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Core/Helpers/MHMHelperFunctions.h"

DEFINE_LOG_CATEGORY_STATIC(LogResurrectionComponent, All, All)

void UMHMResurrectionComponent::BeginPlay()
{
    Super::BeginPlay();
    Health = FMHMHelperFunctions::GetComponentByInterface<IMHMHealth>(GetOwner());
    if (Health)
    {
        Health->OnDead.AddUObject(this, &ThisClass::OnDeath);
    }

    Owner = GetOwner();
}

void UMHMResurrectionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    GetWorldTimerManager().ClearTimer(ResurrectionTimerHandle);
}

void UMHMResurrectionComponent::OnDeath()
{
    if (!GetWorld())
        return;

    GetWorldTimerManager().SetTimer(ResurrectionTimerHandle, this, &ThisClass::ResurrectCharacter, ResurrectionTime,
                                    false);
}

void UMHMResurrectionComponent::ResurrectCharacter()
{
    if (!GetWorld())
        return;

    if (Owner->IsA(AMHMPlayerCharacter::StaticClass()))
    {
        TArray<AActor*> PlayerStarts;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

        if (PlayerStarts.IsEmpty())
            return;

        APlayerStart* RespawnPoint = Cast<APlayerStart>(PlayerStarts[0]);
        if (!RespawnPoint)
            return;

        FTransform RespawnTransform = RespawnPoint->GetActorTransform();
        if (!Owner)
            return;

        FActorSpawnParameters SpawnParams;
        SpawnParams.Template = Owner;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        APawn* NewPawn = GetWorld()->SpawnActor<APawn>(Owner->GetClass(), RespawnTransform, SpawnParams);
        if (!NewPawn)
            return;

        AController* Controller = Cast<AController>(Owner->GetInstigatorController());
        if (!Controller)
            return;

        Controller->Possess(NewPawn);
    }

    if (Owner->IsA(AMHMAnimalCharacter::StaticClass()))
    {
        // TODO: Respawn animals logic
    }
}

