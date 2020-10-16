#pragma once

#include "HellWorld.h"
#include "Engine/DataTable.h"
#include "../../Enums/ItemType.h"
#include "ItemData.generated.h"

// 아이템 정보를 나타내기 위한 구조체
USTRUCT()
struct HELLWORLD_API FItemData : 
	public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// 아이템 코드
	UPROPERTY(EditAnywhere)
	FString ItemCode;

	// 아이템 이름
	UPROPERTY(EditAnywhere)
	FText ItemName;

	// 아이템 타입
	UPROPERTY(EditAnywhere)
	EItemType ItemType;

	// 아이템 최대 개수
	UPROPERTY(EditAnywhere)
	int32 ItemMaxCount;

	// 현재 아이템 개수
	UPROPERTY()
	int32 ItemCount;

	// 장착중 상태
	UPROPERTY()
	bool bIsEquipped;

	// 아이템이 월드에 배치되어있을 경우 표시할 StaticMesh 애셋 경로
	UPROPERTY(EditAnywhere)
	FSoftObjectPath WorldStaticMeshPath;

	// 장착 가능한 아이템일 경우 표시할 Static / SkeletalMesh 애셋 경로
	UPROPERTY(EditAnywhere)
	FSoftObjectPath EquipMeshPath;

	// 각기 다른 수치들을 나타내기 위한 변수
	// 무기 : 공격 속도
	// 방어구 : 추가 체력
	UPROPERTY(EditAnywhere)
	float Value1;

	// 무기 : 대미지
	// 방어구 : 인벤토리 최대 슬롯
	UPROPERTY(EditAnywhere)
	float Value2;

	// 임시 변수
	UPROPERTY(EditAnywhere)
	float Value3;

public :
	static FString ItemCodeToDataTableKey(FString itemCode);

	FORCEINLINE bool operator==(const FItemData& value) const
	{
		return (this->ItemCode == value.ItemCode) &&
			(this->ItemCount == value.ItemCount);
	}



};
