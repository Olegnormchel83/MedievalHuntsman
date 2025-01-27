// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/DeveloperSettings.h"
#include "MHMGameSettings.generated.h"

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Game Settings"))
class MEDIEVALHUNTSMAN_API UMHMGameSettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    UPROPERTY(Config, EditDefaultsOnly, Category = "DataTables")
    TSoftObjectPtr<UDataTable> ItemsDataTable;

    UPROPERTY(Config, EditDefaultsOnly, Category = "DataTables")
    TSoftObjectPtr<UDataTable> WeaponsDataTable;
};
