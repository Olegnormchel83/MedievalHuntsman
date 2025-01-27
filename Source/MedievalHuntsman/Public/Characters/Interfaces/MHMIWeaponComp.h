// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MHMIWeaponComp.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnWeaponChanged);

class AMHMWeapon;

UINTERFACE(MinimalAPI)
class UMHMIWeaponComp : public UInterface
{
	GENERATED_BODY()
};

class MEDIEVALHUNTSMAN_API IMHMIWeaponComp
{
	GENERATED_BODY()

public:
    virtual void EquipWeapon(AMHMWeapon* InWeapon) = 0;
    virtual void AddWeaponToInventory(AMHMWeapon* InWeapon) = 0;
    virtual void HideCurrentWeapon() = 0;
    virtual bool IsInventoryFull() const = 0;
    virtual void RemoveWeapon(AMHMWeapon* WeaponToRemove) = 0;
    virtual AMHMWeapon* GetCurrentWeapon() const = 0;
    virtual TArray<AMHMWeapon*> GetAllWeapons() const = 0;
    virtual bool HasWeapon(AMHMWeapon* TargetWeapon) const = 0;
    virtual bool IsPlayerHoldingWeapon() const = 0;
    virtual void NextWeapon() = 0;
    virtual void PreviousWeapon() = 0;
    virtual FOnWeaponChanged& OnWeaponChanged() = 0;
};
