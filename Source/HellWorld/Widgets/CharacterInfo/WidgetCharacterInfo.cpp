#include "WidgetCharacterInfo.h"

#include "../../Actors/Controllers/PlayerController/TPSPlayerController.h"

#include "WidgetItemSlot.h"
#include "../../Actors/WorldItem/WorldItem.h"
#include "../../Enums/ItemSlotType.h"

#include "Components/ScrollBox.h"


UWidgetCharacterInfo::UWidgetCharacterInfo(const FObjectInitializer & ObjInitializer) :
	Super(ObjInitializer)
{
	LoadAsset();
}

void UWidgetCharacterInfo::LoadAsset()
{
	static ConstructorHelpers::FClassFinder<UWidgetItemSlot> WIDGET_ITEM_SLOT_CLASS (
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/WidgetBP_ItemSlot.WidgetBP_ItemSlot_C'"));

	if (WIDGET_ITEM_SLOT_CLASS.Succeeded())
		ItemSlotWidgetClass = WIDGET_ITEM_SLOT_CLASS.Class;
}

void UWidgetCharacterInfo::FindAllWidget()
{
	VicinityItemView = Cast<UScrollBox>(GetWidgetFromName(TEXT("ScrollBox_VicinityItems")));
	InventoryItemView = Cast<UScrollBox>(GetWidgetFromName(TEXT("ScrollBox_Inventory")));
}

UWidgetItemSlot* UWidgetCharacterInfo::CreateItemSlotWidget()
{
	return CreateWidget<UWidgetItemSlot>(this, ItemSlotWidgetClass);

}

void UWidgetCharacterInfo::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	FindAllWidget();
}

void UWidgetCharacterInfo::InitializeCharacterInfoWidget(ATPSPlayerController* playerController)
{
	PlayerController = playerController;
}

void UWidgetCharacterInfo::AddVicinityItemSlot(class AWorldItem* newItem)
{
	// ������ ������ �����մϴ�.
	UWidgetItemSlot* itemSlotInstance = CreateItemSlotWidget();

	VicinityItemSlotInstances.Add(newItem, itemSlotInstance);

	// ScrollBox �� �߰��մϴ�.
	VicinityItemView->AddChild(itemSlotInstance);

	// ������ ���� �ʱ�ȭ
	itemSlotInstance->InitializeSlot(
		this, 
		*newItem->GetItemData(),
		EItemSlotType::IS_Vicinity,
		newItem);
}

void UWidgetCharacterInfo::RemoveVicinityItemSlot(class AWorldItem* newItem)
{
	// VicinityItemSlotInstances ���� newItem �� ��ġ�ϴ� Ű�� ���� ����� ���� �����մϴ�.
	UWidgetItemSlot* vicinityItemSlotInstance = *VicinityItemSlotInstances.Find(newItem);

	// VicinityItemSlotInstances ���� newItem �� ��ġ�ϴ� Ű�� ���� ��Ҹ� �����մϴ�.
	VicinityItemSlotInstances.Remove(newItem);

	// �θ� �������� SlotWidget �� �����մϴ�.
	//vicinityItemSlotInstance->RemoveFromParent();
	VicinityItemView->RemoveChild(vicinityItemSlotInstance);

}

void UWidgetCharacterInfo::UpdateInventoryItems(const TArray<FItemData>& itemDatas)
{
	// ǥ������ ������ ���Ե� ��� ���� -> �κ��丮 ������ ������� ���Ӱ� ����

	// ���� ǥ������ ���Ե��� �����մϴ�.
	for (auto slotInstances : InventoryItemSlotInstances)
	{
		slotInstances->RemoveFromParent();
	}

	// ǥ������ ���� �迭�� ���ϴ�.
	InventoryItemSlotInstances.Empty();

	for (auto inventoryItemData : itemDatas)
	{
		// ǥ���� ������ ������ �����մϴ�.
		UWidgetItemSlot* itemSlotInstances = CreateItemSlotWidget();

		// ������ ������ ������ �߰��մϴ�.
		InventoryItemView->AddChild(itemSlotInstances);

		// ǥ������ ���� �迭�� �߰��մϴ�.
		InventoryItemSlotInstances.Add(itemSlotInstances);

		// ������ ���� ������ �ʱ�ȭ�մϴ�.
		itemSlotInstances->InitializeSlot(this, inventoryItemData, EItemSlotType::IS_Inventory);
	}
}
