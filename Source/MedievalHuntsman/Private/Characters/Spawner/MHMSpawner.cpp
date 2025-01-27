// MedievalHuntsman. Author: Olegnormchel

#include "Characters/Spawner/MHMSpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Characters/MHMAnimalCharacter.h"

AMHMSpawner::AMHMSpawner()
{
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    check(BoxComponent);

    SetRootComponent(BoxComponent);
    BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMHMSpawner::BeginPlay()
{
    Super::BeginPlay();

    for (uint32 i = 0; i < Count; ++i)
    {
        Spawn();
    }
    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ThisClass::Check, CheckRate, true);
}

void AMHMSpawner::Spawn()
{
    check(GetWorld());
    AActor* Actor = GetWorld()->SpawnActor<AActor>(ActorClass, GetSpawnLocation(), FRotator::ZeroRotator);
    if (Actor)
    {
        Actors.Add(Actor);
        auto SpawnedAnimal = Cast<AMHMAnimalCharacter>(Actor);
        if (SpawnedAnimal)
        {
            SpawnedAnimal->SetAnimalLevel(GenerateAnimalLevel());
        }
    }
    else
    {
        Spawn();
    }
}

uint32 AMHMSpawner::GenerateAnimalLevel() const
{
    uint32 FinalLevel = FMath::RandRange((double)MinLevel, (double)MaxLevel);
    return FinalLevel;
}

FVector AMHMSpawner::GetSpawnLocation() const
{
    check(BoxComponent);
    const FTransform BoxComponentTransform = {BoxComponent->GetComponentRotation(),
                                              BoxComponent->GetComponentLocation(), FVector::OneVector};
    const FVector RandomPoint =
        UKismetMathLibrary::RandomPointInBoundingBox(FVector::ZeroVector, BoxComponent->GetScaledBoxExtent());

    return UKismetMathLibrary::TransformLocation(BoxComponentTransform, RandomPoint);
}

void AMHMSpawner::Check()
{
    const uint32 CountActors = Actors.Num();
    for (uint32 i = 0; i < CountActors; ++i)
    {
        if (!IsValid(Actors[i]))
        {
            Actors.RemoveAt(i);
            Spawn();
        }
    }
}
