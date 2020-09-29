#pragma once

#include "CoreMinimal.h"
#include "PlayerInfo.generated.h"

USTRUCT()
struct HELLWORLD_API FPlayerInfo
{
    GENERATED_USTRUCT_BODY()

public :
    // 플레이어 캐릭터 걷기 속력
    float WalkSpeed;

    // 플레이어 캐릭터 달리기 속력
    float RunSpeed;

public:
    void Initialize();

};
