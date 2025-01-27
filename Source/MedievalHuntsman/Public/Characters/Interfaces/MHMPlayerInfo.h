// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MHMPlayerInfo.generated.h"

class AMHMWeapon;

UINTERFACE(MinimalAPI)
class UMHMPlayerInfo : public UInterface
{
    GENERATED_BODY()
};

class MEDIEVALHUNTSMAN_API IMHMPlayerInfo
{
    GENERATED_BODY()

public:
    virtual void EquipWeapon(AMHMWeapon* InWeapon) = 0;
};
