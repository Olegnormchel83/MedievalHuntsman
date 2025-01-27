// MedievalHuntsman. Author: Olegnormchel

#pragma once

#include "CoreMinimal.h"

class MEDIEVALHUNTSMAN_API FMHMHelperFunctions final
{
public:
    template <class T>
    static T* GetComponentByInterface(const AActor* Actor)
    {
        if (Actor)
        {
            const TArray<UActorComponent*> ActorComponents =
                Actor->GetComponentsByInterface(T::UClassType::StaticClass());
            if (ActorComponents.Num() > 0)
            {
                return Cast<T>(ActorComponents[0]);
            }
            checkNoEntry();
        }
        return nullptr;
    }
};
