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

	// ������ ������ ����ϴ�.
	FItemData* itemData = playerInventory->GetEquippedItemData(EquipSlotIndex);

	// ���� �ؽ�Ʈ�� �����մϴ�.
	ItemNameText->SetText(itemData->ItemName);

}
