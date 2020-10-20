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

	// 인벤토리에 추가된 아이템 데이터들
	TArray<FItemData> InventoryItemDatas;

	// 장착중인 아이템 데이터들
	TArray<FItemData> EquipItemDatas;

public:	
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private :
	// 장비 아이템 슬롯을 초기화합니다.
	void InitializeEquipItemSlots();

public :
	// 인벤토리에 아이템을 추가합니다.
	void AddItem(FItemData itemData);

	// 인벤토리에서 아이템을 제거합니다.
	void RemoveItem(FItemData itemData);

	// 아이템을 장착시킵니다.
	void EquipItem(class UWidgetItemSlot* widgetItemSlot);

	// 전달한 아이템 데이터에 따라 장비 슬롯 인덱스를 반환합니다.
	int32 GetEquipSlotIndex(const FItemData& itemData);

	FORCEINLINE FItemData* GetEquippedItemData(int32 equipSlotIndex)
	{ return &EquipItemDatas[equipSlotIndex]; } 
		
};
