#pragma once

#include "HellWorld.h"
#include "Engine/DataTable.h"
#include "../../Enums/ItemType.h"
#include "ItemData.generated.h"

// ������ ������ ��Ÿ���� ���� ����ü
USTRUCT()
struct HELLWORLD_API FItemData : 
	public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// ������ �ڵ�
	UPROPERTY(EditAnywhere)
	FString ItemCode;

	// ������ �̸�
	UPROPERTY(EditAnywhere)
	FText ItemName;

	// ������ Ÿ��
	UPROPERTY(EditAnywhere)
	EItemType ItemType;

	// ������ �ִ� ����
	UPROPERTY(EditAnywhere)
	int32 ItemMaxCount;

	// ���� ������ ����
	UPROPERTY()
	int32 ItemCount;

	// ������ ����
	UPROPERTY()
	bool bIsEquipped;

	// �������� ���忡 ��ġ�Ǿ����� ��� ǥ���� StaticMesh �ּ� ���
	UPROPERTY(EditAnywhere)
	FSoftObjectPath WorldStaticMeshPath;

	// ���� ������ �������� ��� ǥ���� Static / SkeletalMesh �ּ� ���
	UPROPERTY(EditAnywhere)
	FSoftObjectPath EquipMeshPath;

	// ���� �ٸ� ��ġ���� ��Ÿ���� ���� ����
	// ���� : ���� �ӵ�
	// �� : �߰� ü��
	UPROPERTY(EditAnywhere)
	float Value1;

	// ���� : �����
	// �� : �κ��丮 �ִ� ����
	UPROPERTY(EditAnywhere)
	float Value2;

	// �ӽ� ����
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
