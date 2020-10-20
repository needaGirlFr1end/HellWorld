#include "WidgetCharacterInfo.h"

#include "../../Actors/Controllers/PlayerController/TPSPlayerController.h"

#include "WidgetItemSlot.h"
#include "WidgetEquipItemSlot.h"
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

void UWidgetCharacterInfo::FindEquipItemSlotInstances()
{
	EquipItemSlotInstances.Add(Cast<UWidgetEquipItemSlot>(GetWidgetFromName(TEXT("Widget_Gear"))));
	EquipItemSlotInstances.Add(Cast<UWidgetEquipItemSlot>(GetWidgetFromName(TEXT("Widget_Top"))));
	EquipItemSlotInstances.Add(Cast<UWidgetEquipItemSlot>(GetWidgetFromName(TEXT("Widget_Bottom"))));
	EquipItemSlotInstances.Add(Cast<UWidgetEquipItemSlot>(GetWidgetFromName(TEXT("Widget_Backpack"))));
	EquipItemSlotInstances.Add(Cast<UWidgetEquipItemSlot>(GetWidgetFromName(TEXT("Widget_Weapon1"))));
	EquipItemSlotInstances.Add(Cast<UWidgetEquipItemSlot>(GetWidgetFromName(TEXT("Widget_Weapon2"))));

	for (int32 i = 0; i < EquipItemSlotInstances.Num(); ++i)
		EquipItemSlotInstances[i]->InitializeEquipSlot(this, i);
}

void UWidgetCharacterInfo::FindAllWidget()
{
	VicinityItemView = Cast<UScrollBox>(GetWidgetFromName(TEXT("ScrollBox_VicinityItems")));
	InventoryItemView = Cast<UScrollBox>(GetWidgetFromName(TEXT("ScrollBox_Inventory")));

	FindEquipItemSlotInstances();
}

UWidgetItemSlot* UWidgetCharacterInfo::CreateItemSlotWidget()
{
	// ��Ȱ�� ������ ��ü�� ����ϴ�.
	UWidgetItemSlot* widgetItemSlot = Cast<UWidgetItemSlot>(ItemSlotPool->GetRecycledObject());

	// ���� ��Ȱ�� ������ ��ü�� �������� �ʴ´ٸ�
	if (widgetItemSlot == nullptr)
	{
		// UWidgetItemSlot ��ü�� �����ϸ� ItemSlotPool �� ����ϰ�,
		// widgetItemSlot �� ������ ��ü�� �Ҵ��մϴ�.
		widgetItemSlot = ItemSlotPool->RegisterRecyclableObject(
			CreateWidget<UWidgetItemSlot>(this, ItemSlotWidgetClass));

		UE_LOG(LogTemp, Warning, TEXT("CreateWidget<UWidgetItemSlot>"));
	}

	// ��� ������ ��ü�� ��ȯ�մϴ�.
	return widgetItemSlot;
}

void UWidgetCharacterInfo::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	FindAllWidget();

	ItemSlotPool = NewObject<UObjectPool>();
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

	// ��Ȱ�� ������ ���·� �����մϴ�.
	vicinityItemSlotInstance->SetCanRecyclable(true);
}

void UWidgetCharacterInfo::UpdateInventoryItems(const TArray<FItemData>& itemDatas)
{
	// ǥ������ ������ ���Ե� ��� ���� -> �κ��丮 ������ ������� ���Ӱ� ����

	// ���� ǥ������ ���Ե��� �����մϴ�.
	for (auto slotInstances : InventoryItemSlotInstances)
	{
		slotInstances->RemoveFromParent();

		// ��Ȱ�� ������ ���·� �����մϴ�.
		slotInstances->SetCanRecyclable(true);
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

void UWidgetCharacterInfo::UpdateEquipItem(const TArray<FItemData>& equipItemDatas)
{
	for (int32 i = 0; i < equipItemDatas.Num(); ++i)
		EquipItemSlotInstances[i]->UpdateSlot();
}
