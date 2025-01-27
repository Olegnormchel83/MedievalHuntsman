// MedievalHuntsman. Author: Olegnormchel

#include "WorldObjects/Border/MHMBorder.h"
#include "Components/BoxComponent.h"

AMHMBorder::AMHMBorder() : Super()
{
    ExternalBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ExternalBoxComponent"));
    check(ExternalBoxComponent);
    ExternalBoxComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnExternalBoxComponentEndOverlap);
    SetRootComponent(ExternalBoxComponent);

    InternalBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("InternalBoxComponent"));
    check(InternalBoxComponent);
    InternalBoxComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnInternalBoxComponentEndOverlap);
    InternalBoxComponent->SetupAttachment(ExternalBoxComponent);
}

void AMHMBorder::OnExternalBoxComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (Player)
    {
        Player->SetActorLocation(Location);
    }
}

void AMHMBorder::OnInternalBoxComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    check(OtherActor);
    Player = OtherActor;
    Location = OtherActor->GetActorLocation();
}
