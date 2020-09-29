#pragma once

#include "CoreMinimal.h"
#include "PlayerInfo.generated.h"

USTRUCT()
struct HELLWORLD_API FPlayerInfo
{
    GENERATED_USTRUCT_BODY()

public :
    // �÷��̾� ĳ���� �ȱ� �ӷ�
    float WalkSpeed;

    // �÷��̾� ĳ���� �޸��� �ӷ�
    float RunSpeed;

public:
    void Initialize();

};
