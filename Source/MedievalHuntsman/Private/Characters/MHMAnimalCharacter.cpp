// MedievalHuntsman. Author: Olegnormchel

#include "Characters/MHMAnimalCharacter.h"
#include "Characters/Components/MHMAnimalStatsComponent.h"
#include "Characters/Interfaces/MHMAIController.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogAnimalCharacter, All, All);

AMHMAnimalCharacter::AMHMAnimalCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    bUseControllerRotationYaw = false;

    check(GetCharacterMovement());
    GetCharacterMovement()->bOrientRotationToMovement = true;

    BlockCollisionBody = CreateDefaultSubobject<UBoxComponent>(TEXT("BlockCollisionBody"));
    check(BlockCollisionBody);

    BlockCollisionHead = CreateDefaultSubobject<UBoxComponent>(TEXT("BlockCollisionHead"));
    check(BlockCollisionBody);

    BlockCollisionBody->SetupAttachment(GetRootComponent());
    BlockCollisionHead->SetupAttachment(GetRootComponent());

    AnimalStatsComponent = CreateDefaultSubobject<UMHMAnimalStatsComponent>(TEXT("StatsComponent"));
    check(AnimalStatsComponent);
}

void AMHMAnimalCharacter::BeginPlay()
{
    Super::BeginPlay();
}

bool AMHMAnimalCharacter::IsAgressive() const
{
    return bIsAgressive;
}

void AMHMAnimalCharacter::SetAnimalLevel(float InLevel)
{
    check(AnimalStatsComponent);
    AnimalStatsComponent->SetAnimalLevel(InLevel);
}