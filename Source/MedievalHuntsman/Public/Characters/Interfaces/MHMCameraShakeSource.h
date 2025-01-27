// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MHMCameraShakeSource.generated.h"

UINTERFACE(MinimalAPI)
class UMHMCameraShakeSource : public UInterface
{
    GENERATED_BODY()
};

class MEDIEVALHUNTSMAN_API IMHMCameraShakeSource
{
    GENERATED_BODY()

public:
    virtual void StartShaking() = 0;
    virtual void StopShaking() = 0;
};
