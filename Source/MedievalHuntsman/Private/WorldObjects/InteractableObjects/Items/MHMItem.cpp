// MedievalHuntsman. Author: Olegnormchel


#include "WorldObjects/InteractableObjects/Items/MHMItem.h"
#include "Core/Helpers/MHMItemHelper.h"
#include "Core/Interfaces/MHMInventory.h"
#include "Core/Helpers/MHMHelperFunctions.h"

void AMHMItem::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    ItemRow.DataTable = FMHMItemHelper::GetItemDataTable();
    if (!ItemRow.RowName.IsNone())
    {
        InitMesh();
    }
}

void AMHMItem::InitMesh()
{
    check(StaticMeshComponent);
    StaticMeshComponent->SetStaticMesh(FMHMItemHelper::GetItemStaticMesh(ItemRow.RowName));
}

void AMHMItem::DoInteract(AActor* OtherActor)
{
    Super::DoInteract(OtherActor);
    IMHMInventory* Inventory = FMHMHelperFunctions::GetComponentByInterface<IMHMInventory>(OtherActor);
    if (Inventory)
    {
        Inventory->AddItem(ItemRow.RowName);
        Destroy();
    }
}
