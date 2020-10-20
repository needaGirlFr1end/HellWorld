#include "InventoryComponent.h"

#include "../../Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "../../Actors/Controllers/PlayerController/TPSPlayerController.h"
#include "../../Widgets/CharacterInfo/WidgetCharacterInfo.h"
#include "../../Widgets/CharacterInfo/WidgetItemSlot.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	CharacterInfoWidget = PlayerCharacter->GetPlayerController()->GetCharacterInfoWidgetInstance();

	// 아이템 슬롯 초기화
	InitializeEquipItemSlots();

}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventoryComponent::InitializeEquipItemSlots()
{
	EquipItemDatas.Empty();

	for (int32 i = 0; i < EQUIP_SLOT_COUNT; ++i)
	{
		FItemData slotItemData;
		slotItemData.ItemType = EItemType::IT_None;
		EquipItemDatas.Add(slotItemData);
	}
}

void UInventoryComponent::AddItem(FItemData itemData)
{
	// 아이템 정보를 추가합니다.
	InventoryItemDatas.Add(itemData);

	// UI 에 표시합니다.
	CharacterInfoWidget->UpdateInventoryItems(InventoryItemDatas);

}

void UInventoryComponent::RemoveItem(FItemData itemData)
{
	// InventoryItemDatas 배열에서 itemData 일치하는 요소의 인덱스를 저장합니다.
	int32 inventorySlotIndex = InventoryItemDatas.Find(itemData);
	/// - TArray.Find() 로 사용될 데이터의 형식에는 == 연산자가 오버로드 되어있어야 합니다.

	if (inventorySlotIndex == INDEX_NONE) return;

	// inventorySlotIndex 와 일치하는 인덱스를 갖는 요소를 제거합니다.
	InventoryItemDatas.RemoveAt(inventorySlotIndex);

	// 위젯에 변경된 정보를 업데이트 합니다.
	CharacterInfoWidget->UpdateInventoryItems(InventoryItemDatas);
}

void UInventoryComponent::EquipItem(UWidgetItemSlot* widgetItemSlot)
{
	// 장착시키려는 아이템 정보를 저장합니다.
	FItemData slotItemData = widgetItemSlot->GetItemData();
	
	// 현재 소지중인 아이템 정보를 제거하기 위해 인벤토리에서의 인덱스 번호를 얻습니다.
	int32 findIndex = InventoryItemDatas.Find(slotItemData);

	// 만약 제거하려는 아이템 정보가 존재하지 않는다면
	if (findIndex == INDEX_NONE) return;

	// 인벤토리 정보중 장착시키려는 아이템의 정보를 제거합니다.
	InventoryItemDatas.RemoveAt(findIndex);

	// 아이템이 장착될 배열 인덱스를 얻습니다.
	int32 equipSlotIndex = GetEquipSlotIndex(slotItemData);

	// 장착시킬 아이템의 정보를 적용시킵니다.
	EquipItemDatas[equipSlotIndex].ApplyItemData(&slotItemData);

	// 소지중인 아이템 정보들을 Widget 에 업데이트시킵니다.
	CharacterInfoWidget->UpdateInventoryItems(InventoryItemDatas);

	// 장착중인 아이템의 정보들을 Wiwdget 에 업데이트 시킵니다.
	CharacterInfoWidget->UpdateEquipItem(EquipItemDatas);


	for (int32 i = 0; i < EQUIP_SLOT_COUNT; ++i)
	{
		UE_LOG(LogTemp, Warning, TEXT("itemName = %s"),
			*EquipItemDatas[i].ItemName.ToString());
	}


}

int32 UInventoryComponent::GetEquipSlotIndex(const FItemData& itemData)
{
	switch (itemData.ItemType)
	{
	case EItemType::IT_Gear:		return EQUIP_GEAR;
	case EItemType::IT_Top :		return EQUIP_TOP;
	case EItemType::IT_Bottom :		return EQUIP_BOTTOM;
	case EItemType::IT_Backpack:	return EQUIP_BACKPACK;
	case EItemType::IT_Weapon :

		// 첫번째 칸이 비어있을 경우 첫번째 칸을 반환
		if (EquipItemDatas[EQUIP_LEFT_WEAPON].ItemType == EItemType::IT_None)
			return EQUIP_LEFT_WEAPON;

		// 두번째 칸이 비어있을 경우 두번째 칸을 반환
		else if (EquipItemDatas[EQUIP_RIGHT_WEAPON].ItemType == EItemType::IT_None)
			return EQUIP_RIGHT_WEAPON;

		// 둘 다 차있을 경우 첫번째 칸을 반환
		else return EQUIP_LEFT_WEAPON;
	}

	return INDEX_NONE;
}
