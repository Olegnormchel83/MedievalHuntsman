// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MHMHUD.generated.h"

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API AMHMHUD final : public AHUD
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
};
