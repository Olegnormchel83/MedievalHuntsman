// MedievalHuntsman. Author: Olegnormchel

#include "WorldObjects/InteractableObjects/MHMInteractableObject.h"

AMHMInteractableObject::AMHMInteractableObject() : Super()
{
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    SetRootComponent(StaticMeshComponent);

    SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
}

void AMHMInteractableObject::Interact(AActor* OtherActor)
{
    if (CanInteract())
    {
        DoInteract(OtherActor);
    }
}

bool AMHMInteractableObject::CanInteract() const
{
    return true;
}

void AMHMInteractableObject::DoInteract(AActor* OtherActor)
{
}

void AMHMInteractableObject::OnEnter()
{
}

void AMHMInteractableObject::OnLeave()
{
}
