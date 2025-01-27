// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MHMAnimalStats.generated.h"

UINTERFACE(MinimalAPI)
class UMHMAnimalStats : public UInterface
{
	GENERATED_BODY()
};


class MEDIEVALHUNTSMAN_API IMHMAnimalStats
{
	GENERATED_BODY()

public:
    virtual float GetAttackSpeed() const = 0;
    virtual float GetDamage() const = 0;

	virtual void SetAnimalLevel(uint32 InAnimalLevel) = 0;
};
