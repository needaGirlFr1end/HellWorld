#include "WidgetCharacterInfo.h"

#include "WidgetItemSlot.h"
#include "../../Actors/WorldItem/WorldItem.h"

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
		newItem);
}