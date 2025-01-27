// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MHMExperience.generated.h"

UINTERFACE(MinimalAPI)
class UMHMExperience : public UInterface
{
	GENERATED_BODY()
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnLevelUp, bool);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnLevelDown, bool);

class MEDIEVALHUNTSMAN_API IMHMExperience
{
	GENERATED_BODY()

public:
    FOnLevelUp OnLevelUp;
    FOnLevelDown OnLevelDown;

    virtual void AddExperience(const int32 AddValue) = 0;
    virtual void ReduceExperience(const int32 ReduceValue) = 0;
    virtual int32 CalculateExperienceForNextLevel(const int32 InLevel) = 0;
    virtual int32 GetCurrentLevel() const = 0;
};
