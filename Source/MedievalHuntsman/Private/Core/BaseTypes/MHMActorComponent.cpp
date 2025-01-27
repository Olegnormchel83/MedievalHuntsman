// MedievalHuntsman. Author: Olegnormchel

#include "Core/BaseTypes/MHMActorComponent.h"

FTimerManager& UMHMActorComponent::GetWorldTimerManager() const
{
    check(GetWorld());
    return GetWorld()->GetTimerManager();
}
