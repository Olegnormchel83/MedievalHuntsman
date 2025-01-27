// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "Characters/Interfaces/MHMIWeaponComp.h"
#include "Core/BaseTypes/MHMActorComponent.h"
#include "MHMWeaponComponent.generated.h"

class AMHMWeapon;

UCLASS()
class MEDIEVALHUNTSMAN_API UMHMWeaponComponent final : public UMHMActorComponent, public IMHMIWeaponComp
{
    GENERATED_BODY()

public:
    virtual void EquipWeapon(AMHMWeapon* InWeapon) override;
    virtual void AddWeaponToInventory(AMHMWeapon* InWeapon) override;
    virtual void HideCurrentWeapon() override;
    virtual bool IsInventoryFull() const override;
    virtual void RemoveWeapon(AMHMWeapon* WeaponToRemove) override;
    virtual AMHMWeapon* GetCurrentWeapon() const override;
    virtual TArray<AMHMWeapon*> GetAllWeapons() const override;
    virtual bool HasWeapon(AMHMWeapon* TargetWeapon) const override;
    virtual bool IsPlayerHoldingWeapon() const override;
    virtual void NextWeapon() override;
    virtual void PreviousWeapon() override;
    virtual FOnWeaponChanged& OnWeaponChanged() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings",
              meta = (ClampMin = "1", UIMin = "1", ClampMax = "4", UIMax = "4"))
    int32 MaxWeaponsCount = 4;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    TSubclassOf<AMHMWeapon> StartingWeapon;

    TArray<AMHMWeapon*> Weapons;
    AMHMWeapon* CurrentWeapon;
    FOnWeaponChanged OnWeaponChangedEvent;
    
    void LogInfoAboutWeapons();
};
