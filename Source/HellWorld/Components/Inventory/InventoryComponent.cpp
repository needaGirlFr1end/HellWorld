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

	// ������ ���� �ʱ�ȭ
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
	// ������ ������ �߰��մϴ�.
	InventoryItemDatas.Add(itemData);

	// UI �� ǥ���մϴ�.
	CharacterInfoWidget->UpdateInventoryItems(InventoryItemDatas);

}

void UInventoryComponent::RemoveItem(FItemData itemData)
{
	// InventoryItemDatas �迭���� itemData ��ġ�ϴ� ����� �ε����� �����մϴ�.
	int32 inventorySlotIndex = InventoryItemDatas.Find(itemData);
	/// - TArray.Find() �� ���� �������� ���Ŀ��� == �����ڰ� �����ε� �Ǿ��־�� �մϴ�.

	if (inventorySlotIndex == INDEX_NONE) return;

	// inventorySlotIndex �� ��ġ�ϴ� �ε����� ���� ��Ҹ� �����մϴ�.
	InventoryItemDatas.RemoveAt(inventorySlotIndex);

	// ������ ����� ������ ������Ʈ �մϴ�.
	CharacterInfoWidget->UpdateInventoryItems(InventoryItemDatas);
}

void UInventoryComponent::EquipItem(UWidgetItemSlot* widgetItemSlot)
{
	// ������Ű���� ������ ������ �����մϴ�.
	FItemData slotItemData = widgetItemSlot->GetItemData();
	
	// ���� �������� ������ ������ �����ϱ� ���� �κ��丮������ �ε��� ��ȣ�� ����ϴ�.
	int32 findIndex = InventoryItemDatas.Find(slotItemData);

	// ���� �����Ϸ��� ������ ������ �������� �ʴ´ٸ�
	if (findIndex == INDEX_NONE) return;

	// �κ��丮 ������ ������Ű���� �������� ������ �����մϴ�.
	InventoryItemDatas.RemoveAt(findIndex);

	// �������� ������ �迭 �ε����� ����ϴ�.
	int32 equipSlotIndex = GetEquipSlotIndex(slotItemData);

	// ������ų �������� ������ �����ŵ�ϴ�.
	EquipItemDatas[equipSlotIndex].ApplyItemData(&slotItemData);

	// �������� ������ �������� Widget �� ������Ʈ��ŵ�ϴ�.
	CharacterInfoWidget->UpdateInventoryItems(InventoryItemDatas);

	// �������� �������� �������� Wiwdget �� ������Ʈ ��ŵ�ϴ�.
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

		// ù��° ĭ�� ������� ��� ù��° ĭ�� ��ȯ
		if (EquipItemDatas[EQUIP_LEFT_WEAPON].ItemType == EItemType::IT_None)
			return EQUIP_LEFT_WEAPON;

		// �ι�° ĭ�� ������� ��� �ι�° ĭ�� ��ȯ
		else if (EquipItemDatas[EQUIP_RIGHT_WEAPON].ItemType == EItemType::IT_None)
			return EQUIP_RIGHT_WEAPON;

		// �� �� ������ ��� ù��° ĭ�� ��ȯ
		else return EQUIP_LEFT_WEAPON;
	}

	return INDEX_NONE;
}
