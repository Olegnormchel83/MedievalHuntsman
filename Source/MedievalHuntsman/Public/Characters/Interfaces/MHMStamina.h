// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MHMStamina.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnRanOutStamina);
DECLARE_MULTICAST_DELEGATE(FOnChangedStamina);

UINTERFACE(MinimalAPI)
class UMHMStamina : public UInterface
{
	GENERATED_BODY()
};


class MEDIEVALHUNTSMAN_API IMHMStamina
{
	GENERATED_BODY()

public:
    virtual void UseStamina(const float UsedStamina) = 0;
    virtual float GetCurrentStamina() const = 0;
    virtual float GetPercentStamina() const = 0;
    virtual FOnChangedStamina& OnChangedStamina() = 0;
    virtual FOnRanOutStamina& OnRanOutStamina() = 0;
};
