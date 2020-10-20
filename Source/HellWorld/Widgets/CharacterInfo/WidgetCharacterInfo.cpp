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
	// 재활용 가능한 객체를 얻습니다.
	UWidgetItemSlot* widgetItemSlot = Cast<UWidgetItemSlot>(ItemSlotPool->GetRecycledObject());

	// 만약 재활용 가능한 객체가 존재하지 않는다면
	if (widgetItemSlot == nullptr)
	{
		// UWidgetItemSlot 객체를 생성하며 ItemSlotPool 에 등록하고,
		// widgetItemSlot 에 생성한 객체를 할당합니다.
		widgetItemSlot = ItemSlotPool->RegisterRecyclableObject(
			CreateWidget<UWidgetItemSlot>(this, ItemSlotWidgetClass));

		UE_LOG(LogTemp, Warning, TEXT("CreateWidget<UWidgetItemSlot>"));
	}

	// 사용 가능한 객체를 반환합니다.
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
	// 아이템 슬롯을 생성합니다.
	UWidgetItemSlot* itemSlotInstance = CreateItemSlotWidget();

	VicinityItemSlotInstances.Add(newItem, itemSlotInstance);

	// ScrollBox 에 추가합니다.
	VicinityItemView->AddChild(itemSlotInstance);

	// 아이템 슬롯 초기화
	itemSlotInstance->InitializeSlot(
		this, 
		*newItem->GetItemData(),
		EItemSlotType::IS_Vicinity,
		newItem);
}

void UWidgetCharacterInfo::RemoveVicinityItemSlot(class AWorldItem* newItem)
{
	// VicinityItemSlotInstances 에서 newItem 와 일치하는 키를 갖는 요소의 값을 저장합니다.
	UWidgetItemSlot* vicinityItemSlotInstance = *VicinityItemSlotInstances.Find(newItem);

	// VicinityItemSlotInstances 에서 newItem 와 일치하는 키를 갖는 요소를 제거합니다.
	VicinityItemSlotInstances.Remove(newItem);

	// 부모 위젯에서 SlotWidget 을 제거합니다.
	//vicinityItemSlotInstance->RemoveFromParent();
	VicinityItemView->RemoveChild(vicinityItemSlotInstance);

	// 재활용 가능한 상태로 변경합니다.
	vicinityItemSlotInstance->SetCanRecyclable(true);
}

void UWidgetCharacterInfo::UpdateInventoryItems(const TArray<FItemData>& itemDatas)
{
	// 표시중인 아이템 슬롯들 모두 제거 -> 인벤토리 아이템 정보들로 새롭게 생성

	// 현재 표시중인 슬롯들을 제거합니다.
	for (auto slotInstances : InventoryItemSlotInstances)
	{
		slotInstances->RemoveFromParent();

		// 재활용 가능한 상태로 변경합니다.
		slotInstances->SetCanRecyclable(true);
	}

	// 표시중인 슬롯 배열을 비웁니다.
	InventoryItemSlotInstances.Empty();

	for (auto inventoryItemData : itemDatas)
	{
		// 표시할 아이템 슬롯을 생성합니다.
		UWidgetItemSlot* itemSlotInstances = CreateItemSlotWidget();

		// 아이템 슬롯을 위젯에 추가합니다.
		InventoryItemView->AddChild(itemSlotInstances);

		// 표시중인 슬롯 배열에 추가합니다.
		InventoryItemSlotInstances.Add(itemSlotInstances);

		// 아이템 슬롯 정보를 초기화합니다.
		itemSlotInstances->InitializeSlot(this, inventoryItemData, EItemSlotType::IS_Inventory);
	}
}

void UWidgetCharacterInfo::UpdateEquipItem(const TArray<FItemData>& equipItemDatas)
{
	for (int32 i = 0; i < equipItemDatas.Num(); ++i)
		EquipItemSlotInstances[i]->UpdateSlot();
}
