// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MHMAIController.generated.h"

UINTERFACE(MinimalAPI)
class UMHMAIController : public UInterface
{
	GENERATED_BODY()
};

class MEDIEVALHUNTSMAN_API IMHMAIController
{
	GENERATED_BODY()

	
public:
    virtual void SeeActor(AActor* Actor) = 0;
    virtual void DamageHasBeenReceived(AActor* DamageCauser) = 0;
};
