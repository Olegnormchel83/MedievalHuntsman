// MedievalHuntsman. Author: Olegnormchel

#include "Core/Components/MHMInventoryComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogInventoryComponent, All, All);

void UMHMInventoryComponent::AddItem(const FName& RowName, const uint32 Count)
{
    check(!RowName.IsNone());
    check(Count > 0);
    if (Items.Contains(RowName))
    {
        Items[RowName] += Count;
    }
    else
    {
        Items.Add(RowName, Count);
    }
    OnInventoryChangedEvent.Broadcast();
}

void UMHMInventoryComponent::TransferFromInventory(IMHMInventory* OtherInventory)
{
    check(OtherInventory);
    const TMap<FName, uint32> OtherItems = OtherInventory->GetItems();

    for (const TPair<FName, uint32> Pair : OtherItems)
    {
        AddItem(Pair.Key, Pair.Value);
        if (!OtherInventory->RemoveItem(Pair.Key, Pair.Value))
        {
            checkNoEntry();
        }
    }
}

const TMap<FName, uint32>& UMHMInventoryComponent::GetItems() const
{
    return Items;
}

bool UMHMInventoryComponent::HasItem(const FName& RowName) const
{
    return Items.Contains(RowName);
}

uint32 UMHMInventoryComponent::GetCountByRowName(const FName& RowName) const
{
    if (HasItem(RowName))
    {
        return Items[RowName];
    }
    return 0;
}

bool UMHMInventoryComponent::RemoveItem(const FName& RowName, const uint32 Count)
{
    if (!Items.Contains(RowName))
        return false;

    if (Items[RowName] < Count)
        return false;

    Items[RowName] -= Count;
    if (Items[RowName] == 0)
    {
        Items.Remove(RowName);
    }

    OnInventoryChangedEvent.Broadcast();
    return true;
}

FOnInventoryChanged& UMHMInventoryComponent::OnInventoryChanged()
{
    return OnInventoryChangedEvent;
}
