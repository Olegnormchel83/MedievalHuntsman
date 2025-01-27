// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"
#include "WorldObjects/MHMWorldObject.h"
#include "MHMBorder.generated.h"

class UBoxComponent;

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API AMHMBorder final : public AMHMWorldObject
{
    GENERATED_BODY()

public:
    AMHMBorder();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UBoxComponent* ExternalBoxComponent;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UBoxComponent* InternalBoxComponent;

private:
    UPROPERTY()
    AActor* Player;

    FVector Location;

    UFUNCTION()
    void OnExternalBoxComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UFUNCTION()
    void OnInternalBoxComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
