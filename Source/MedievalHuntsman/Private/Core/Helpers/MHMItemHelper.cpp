// MedievalHuntsman. Author: Olegnormchel


#include "Core/Helpers/MHMItemHelper.h"
#include "Core/BaseTypes/MHMCoreTypes.h"
#include "Core/Helpers/MHMDataTableHelper.h"
#include "Core/Settings/MHMGameSettings.h"

//Item
const UDataTable* FMHMItemHelper::GetItemDataTable()
{
    const UMHMGameSettings* GameSettings = GetDefault<UMHMGameSettings>();
    check(GameSettings);
    return GameSettings->ItemsDataTable.LoadSynchronous();
}

FMHMItemInfo* FMHMItemHelper::GetItemInfo(const FName& RowName)
{
    return FMHMDataTableHelper::FindRow<FMHMItemInfo>(GetItemDataTable(), RowName);
}

FText FMHMItemHelper::GetItemName(const FName& RowName)
{
    const FMHMItemInfo* ItemInfo = GetItemInfo(RowName);
    check(ItemInfo);
    return ItemInfo->Name;
}

UStaticMesh* FMHMItemHelper::GetItemStaticMesh(const FName& RowName)
{
    const FMHMItemInfo* ItemInfo = GetItemInfo(RowName);
    check(ItemInfo);
    return ItemInfo->StaticMesh;
}

//Weapon
const UDataTable* FMHMItemHelper::GetWeaponDataTable()
{
    const UMHMGameSettings* GameSettings = GetDefault<UMHMGameSettings>();
    check(GameSettings);
    return GameSettings->WeaponsDataTable.LoadSynchronous();
}


FMHMWeaponInfo* FMHMItemHelper::GetWeaponInfo(const FName& RowName)
{
    return FMHMDataTableHelper::FindRow<FMHMWeaponInfo>(GetWeaponDataTable(), RowName);
}


FText FMHMItemHelper::GetWeaponName(const FName& RowName)
{
    const FMHMWeaponInfo* WeaponInfo = GetWeaponInfo(RowName);
    check(WeaponInfo);
    return WeaponInfo->Name;
}


UStaticMesh* FMHMItemHelper::GetWeaponStaticMesh(const FName& RowName)
{
    const FMHMWeaponInfo* WeaponInfo = GetWeaponInfo(RowName);
    check(WeaponInfo);
    return WeaponInfo->StaticMesh;
}

USkeletalMesh* FMHMItemHelper::GetWeaponSkeletalMesh(const FName& RowName)
{
    const FMHMWeaponInfo* WeaponInfo = GetWeaponInfo(RowName);
    check(WeaponInfo);
    return WeaponInfo->SkeletalMesh;
}
