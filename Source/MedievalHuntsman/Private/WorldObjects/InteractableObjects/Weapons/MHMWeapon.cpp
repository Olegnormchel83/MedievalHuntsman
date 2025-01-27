// MedievalHuntsman. Author: Olegnormchel

#include "WorldObjects/InteractableObjects/Weapons/MHMWeapon.h"
#include "Core/Helpers/MHMItemHelper.h"
#include "Characters/Interfaces/MHMIWeaponComp.h"
#include "Core/Helpers/MHMHelperFunctions.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeapon, All, All);

void AMHMWeapon::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    WeaponRow.DataTable = FMHMItemHelper::GetWeaponDataTable();
    if (!WeaponRow.RowName.IsNone())
    {
        InitMesh();
    }
}

void AMHMWeapon::InitMesh()
{
    if (StaticMeshComponent)
    {
        StaticMeshComponent->DestroyComponent();
    }

    if (SkeletalMeshComponent)
    {
        SkeletalMeshComponent->SetSkeletalMesh(FMHMItemHelper::GetWeaponSkeletalMesh(WeaponRow.RowName));
    }

    if (GetOwner())
    {
        UE_LOG(LogWeapon, Warning, TEXT("%s's Owner: %s"), *GetName(), *GetOwner()->GetName());
    }
}

void AMHMWeapon::DoInteract(AActor* OtherActor)
{
    Super::DoInteract(OtherActor);

    UE_LOG(LogWeapon, Warning, TEXT("AMHMWeapon::DoInteract"));

    IMHMIWeaponComp* IWeapon = FMHMHelperFunctions::GetComponentByInterface<IMHMIWeaponComp>(OtherActor);
    if (IWeapon)
    {
        if (IWeapon->IsInventoryFull())
        {
            return;
        }

        if (!IWeapon->IsPlayerHoldingWeapon())
        {
            SkeletalMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
            IWeapon->EquipWeapon(this);
            IWeapon->AddWeaponToInventory(this);

            UE_LOG(LogWeapon, Warning, TEXT("Weapon equiped"));
            return;
        }

        if (!IWeapon->IsInventoryFull() && IWeapon->IsPlayerHoldingWeapon())
        {
            UE_LOG(LogWeapon, Display, TEXT("CurrentPlayerWeapon: %s"), *IWeapon->GetCurrentWeapon()->GetName());

            SkeletalMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
            IWeapon->AddWeaponToInventory(this);
            SetActorEnableCollision(false);
            SetActorHiddenInGame(true);
            DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
            SetOwner(OtherActor);
            UE_LOG(LogWeapon, Warning, TEXT("Weapon added to inventory"));
        }
    }
}
