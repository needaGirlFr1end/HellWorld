#pragma once

#include "HellWorld.h"
#include "Components/ActorComponent.h"

#include "../../Structures/ItemData/ItemData.h"

#include "InventoryComponent.generated.h"


UCLASS()
class HELLWORLD_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

private : 
	class APlayerCharacter* PlayerCharacter;
	class UWidgetCharacterInfo* CharacterInfoWidget;

	// �κ��丮�� �߰��� ������ �����͵�
	TArray<FItemData> InventoryItemDatas;

	// �������� ������ �����͵�
	TArray<FItemData> EquipItemDatas;

public:	
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private :
	// ��� ������ ������ �ʱ�ȭ�մϴ�.
	void InitializeEquipItemSlots();

public :
	// �κ��丮�� �������� �߰��մϴ�.
	void AddItem(FItemData itemData);

	// �κ��丮���� �������� �����մϴ�.
	void RemoveItem(FItemData itemData);

	// �������� ������ŵ�ϴ�.
	void EquipItem(class UWidgetItemSlot* widgetItemSlot);

	// ������ ������ �����Ϳ� ���� ��� ���� �ε����� ��ȯ�մϴ�.
	int32 GetEquipSlotIndex(const FItemData& itemData);

	FORCEINLINE FItemData* GetEquippedItemData(int32 equipSlotIndex)
	{ return &EquipItemDatas[equipSlotIndex]; } 
		
};
