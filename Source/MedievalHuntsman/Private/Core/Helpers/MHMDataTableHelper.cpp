// MedievalHuntsman. Author: Olegnormchel


#include "Core/Helpers/MHMDataTableHelper.h"

const FString FMHMDataTableHelper::ContextString(TEXT("DataTable"));

TArray<FName> FMHMDataTableHelper::GetRowNames(const UDataTable* DataTable)
{
    check(DataTable);
    return DataTable->GetRowNames();
}

bool FMHMDataTableHelper::RowExists(const UDataTable* DataTable, const FName& RowName)
{
    check(DataTable);
    return DataTable->GetRowNames().Contains(RowName);
}
