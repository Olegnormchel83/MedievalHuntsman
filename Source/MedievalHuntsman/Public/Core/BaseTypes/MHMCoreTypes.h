// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MHMCoreTypes.generated.h"

UENUM(BlueprintType)
enum class EMHMItemType : uint8
{
    Other = 0,
    Weapon,
    Arrow,
    Money
};

USTRUCT(BlueprintType)
struct FMHMItemInfo : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly)
    FText Name;

    UPROPERTY(EditDefaultsOnly)
    EMHMItemType ItemType = EMHMItemType::Other;

    UPROPERTY(EditDefaultsOnly)
    UTexture2D* Thumbnail = nullptr;

    UPROPERTY(EditDefaultsOnly)
    UStaticMesh* StaticMesh = nullptr;

    UPROPERTY(EditDefaultsOnly)
    USkeletalMesh* SkeletalMesh = nullptr;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UAnimInstance> AnimInstanceClass;

    UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0", UIMin = "0"))
    float Price = 0.0f;
};

USTRUCT(BlueprintType)
struct FMHMWeaponInfo : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly)
    FText Name;

    UPROPERTY(VisibleAnywhere)
    EMHMItemType ItemType = EMHMItemType::Weapon;

    UPROPERTY(EditDefaultsOnly)
    UTexture2D* Thumbnail = nullptr;

    UPROPERTY(EditDefaultsOnly)
    UStaticMesh* StaticMesh = nullptr;

    UPROPERTY(EditDefaultsOnly)
    USkeletalMesh* SkeletalMesh = nullptr;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UAnimInstance> AnimInstanceClass;

    UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0", UIMin = "0"))
    float Damage = 0.0f;

    UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0", UIMin = "0"))
    float Price = 0.0f;
};