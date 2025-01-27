// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MHMHealth.generated.h"

UINTERFACE(MinimalAPI)
class UMHMHealth : public UInterface
{
	GENERATED_BODY()
};

DECLARE_MULTICAST_DELEGATE(FOnDead);

class MEDIEVALHUNTSMAN_API IMHMHealth
{
	GENERATED_BODY()

public:
    FOnDead OnDead;

    virtual void SetCurrentHealth(const float InCurrentHealth) = 0;
    virtual void AddHealth(const float AddValue) = 0;
    virtual void ReduceHealth(const float ReduceValue) = 0;
    virtual void Regeneration() = 0;
    virtual void RegenerationTick() = 0;

    virtual float GetMaxHealth() const = 0;
    virtual void SetMaxHealth(const float InMaxHealth) = 0;
    virtual float GetRegenHealthPerSecond() const = 0;
    virtual void SetRegenHealthPerSecond(const float InRegenHealthValue) = 0;
};
