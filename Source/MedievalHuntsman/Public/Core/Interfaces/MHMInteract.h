// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MHMInteract.generated.h"

UINTERFACE(MinimalAPI)
class UMHMInteract : public UInterface
{
	GENERATED_BODY()
};

class MEDIEVALHUNTSMAN_API IMHMInteract
{
	GENERATED_BODY()

public:
    virtual void Interact(AActor* OtherActor) = 0;
    virtual void OnEnter() = 0;
    virtual void OnLeave() = 0;
};
