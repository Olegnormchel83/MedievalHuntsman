// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"

class UDataTable;
class UStaticMesh;
struct FMHMItemInfo;
struct FMHMWeaponInfo;

class MEDIEVALHUNTSMAN_API FMHMItemHelper final
{
public:
    //Item
    static const UDataTable* GetItemDataTable();
    static FMHMItemInfo* GetItemInfo(const FName& RowName);
    static FText GetItemName(const FName& RowName);
    static UStaticMesh* GetItemStaticMesh(const FName& RowName);

    //Weapon
    static const UDataTable* GetWeaponDataTable();
    static FMHMWeaponInfo* GetWeaponInfo(const FName& RowName);
    static FText GetWeaponName(const FName& RowName);
    static UStaticMesh* GetWeaponStaticMesh(const FName& RowName);
    static USkeletalMesh* GetWeaponSkeletalMesh(const FName& RowName);
};
