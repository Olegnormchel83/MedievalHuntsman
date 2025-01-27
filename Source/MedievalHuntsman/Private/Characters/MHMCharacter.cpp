// MedievalHuntsman. Author: Olegnormchel

#include "Characters/MHMCharacter.h"
#include "Characters/Components/MHMAHealthComponent.h"
#include "Characters/Components/MHMCharacterMovementComponent.h"
#include "Core/Components/MHMInventoryComponent.h"
#include "Core/Components/MHMStartingItemsComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AMHMCharacter::AMHMCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<UMHMCharacterMovementComponent>(CharacterMovementComponentName))
{
    HealthComponent = CreateDefaultSubobject<UMHMAHealthComponent>(TEXT("HealthComponent"));
    check(HealthComponent);
    HealthComponent->OnDead.AddUObject(this, &ThisClass::Dead);

    InventoryComponent = CreateDefaultSubobject<UMHMInventoryComponent>(TEXT("InventoryComponent"));
    check(InventoryComponent);

    StartingItemsComponent = CreateDefaultSubobject<UMHMStartingItemsComponent>(TEXT("StartinItemsComponent"));
    check(StartingItemsComponent);
}

void AMHMCharacter::Dead()
{
    UE_LOG(LogTemp, Warning, TEXT("Dead"));
}

UMHMAHealthComponent* AMHMCharacter::GetHealthComponent() const
{
    return HealthComponent;
}
