// MedievalHuntsman. Author: Olegnormchel

#include "Characters/Components/MHMWeaponComponent.h"
#include "Characters/Interfaces/MHMPlayerInfo.h"
#include "WorldObjects/InteractableObjects/Weapons/MHMWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

void UMHMWeaponComponent::EquipWeapon(AMHMWeapon* InWeapon)
{
    check(InWeapon);

    CurrentWeapon = InWeapon;
    OnWeaponChangedEvent.Broadcast();

    IMHMPlayerInfo* PlayerInfo = Cast<IMHMPlayerInfo>(GetOwner());
    if (PlayerInfo)
    {
        PlayerInfo->EquipWeapon(InWeapon);
        UE_LOG(LogWeaponComponent, Warning, TEXT("Equipped weapon: %s"), *InWeapon->GetName());
    }
}

void UMHMWeaponComponent::AddWeaponToInventory(AMHMWeapon* InWeapon)
{
    check(InWeapon);
    Weapons.Add(InWeapon);
}

void UMHMWeaponComponent::HideCurrentWeapon()
{
    int32 CurrentWeaponIndex = Weapons.IndexOfByKey(CurrentWeapon);
    Weapons[CurrentWeaponIndex] = CurrentWeapon;
    CurrentWeapon->SetActorHiddenInGame(true);
    CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    CurrentWeapon = nullptr;

    UE_LOG(LogWeaponComponent, Warning, TEXT("CurrentWeaponHidden"));
}

bool UMHMWeaponComponent::IsInventoryFull() const
{
    return Weapons.Num() == MaxWeaponsCount;
}

void UMHMWeaponComponent::RemoveWeapon(AMHMWeapon* WeaponToRemove)
{
    check(WeaponToRemove);
    check(Weapons.Contains(WeaponToRemove));
    Weapons.Remove(WeaponToRemove);
    if (CurrentWeapon == WeaponToRemove)
    {
        CurrentWeapon = nullptr;
    }
    OnWeaponChangedEvent.Broadcast();

    LogInfoAboutWeapons();
}

AMHMWeapon* UMHMWeaponComponent::GetCurrentWeapon() const
{
    if (CurrentWeapon)
    {
        return CurrentWeapon;
    }
    else
    {
        return nullptr;
    }
}

TArray<AMHMWeapon*> UMHMWeaponComponent::GetAllWeapons() const
{
    return Weapons;
}

bool UMHMWeaponComponent::HasWeapon(AMHMWeapon* TargetWeapon) const
{
    return Weapons.Contains(TargetWeapon);
}

bool UMHMWeaponComponent::IsPlayerHoldingWeapon() const
{
    return CurrentWeapon != nullptr;
}

void UMHMWeaponComponent::NextWeapon()
{
    UE_LOG(LogWeaponComponent, Warning, TEXT("NextWeapon()"));

    if (Weapons.Num() <= 1)
        return;

    int32 CurrentWeaponIndex = Weapons.IndexOfByKey(CurrentWeapon);
    int32 NextWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();

    HideCurrentWeapon();
    CurrentWeapon = Weapons[NextWeaponIndex];
    EquipWeapon(CurrentWeapon);

    OnWeaponChangedEvent.Broadcast();
}

void UMHMWeaponComponent::PreviousWeapon()
{
    UE_LOG(LogWeaponComponent, Warning, TEXT("PreviousWeapon()"));

    if (Weapons.Num() <= 1)
        return;

    int32 CurrentWeaponIndex = Weapons.IndexOfByKey(CurrentWeapon);
    int32 PreviousWeaponIndex = (CurrentWeaponIndex - 1 + Weapons.Num()) % Weapons.Num();

    HideCurrentWeapon();
    CurrentWeapon = Weapons[PreviousWeaponIndex];
    EquipWeapon(CurrentWeapon);

    OnWeaponChangedEvent.Broadcast();
}

void UMHMWeaponComponent::LogInfoAboutWeapons()
{
    UE_LOG(LogWeaponComponent, Warning, TEXT("-----------Weapons--------------"));
    for (AMHMWeapon* Weapon : Weapons)
    {
        UE_LOG(LogWeaponComponent, Warning, TEXT("%s"), *Weapon->GetName());
    }
    UE_LOG(LogWeaponComponent, Warning, TEXT("-------------------------"));
}

FOnWeaponChanged& UMHMWeaponComponent::OnWeaponChanged()
{
    return OnWeaponChangedEvent;
}