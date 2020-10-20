#include "WidgetEquipItemSlot.h"
#include "WidgetCharacterInfo.h"

#include "Components/TextBlock.h"

#include "../../Actors/Controllers/PlayerController/TPSPlayerController.h"
#include "../../Interfaces/PlayerControllable.h"
#include "../../Components/Inventory/InventoryComponent.h"


void UWidgetEquipItemSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	FindAllWidget();

}

void UWidgetEquipItemSlot::FindAllWidget()
{
	GetWidgetFromName(TEXT("Button_Slot"));
	ItemNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_ItemName")));
}

void UWidgetEquipItemSlot::InitializeEquipSlot(UWidgetCharacterInfo* ownerWidget, int32 equipSlotIndex)
{
	OwnerWidget = ownerWidget;
	EquipSlotIndex = equipSlotIndex;
}

void UWidgetEquipItemSlot::UpdateSlot()
{
	UInventoryComponent* playerInventory = OwnerWidget->GetPlayerController()->
		GetControllablePawn()->GetInventoryComponent();

	// 아이템 정보를 얻습니다.
	FItemData* itemData = playerInventory->GetEquippedItemData(EquipSlotIndex);

	// 슬롯 텍스트를 설정합니다.
	ItemNameText->SetText(itemData->ItemName);

}
