#include "WidgetItemSlot.h"

#include "../../Actors/WorldItem/WorldItem.h"
#include "../../Actors/Controllers/PlayerController/TPSPlayerController.h"
#include "../../Actors/Characters/PlayerCharacter/PlayerCharacter.h"

#include "../../Interfaces/PlayerControllable.h"

#include "../../Components/Inventory/InventoryComponent.h"
#include "WidgetCharacterInfo.h"


#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"


void UWidgetItemSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	FindAllWidget();

	// ��ư ���� Ŭ���� ȣ���� �޼��� ���
	SlotButton->OnReleased.AddDynamic(this, &UWidgetItemSlot::OnWidgetLeftClicked);
}

void UWidgetItemSlot::FindAllWidget()
{
	SlotButton = Cast<UButton>(GetWidgetFromName(TEXT("Button_Slot")));
	SlotLineImage = Cast<UImage>(GetWidgetFromName(TEXT("Image_Line")));
	ItemNameTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_ItemName")));
	ItemCountTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_ItemCount")));
}


void UWidgetItemSlot::InitializeSlot(
	UWidgetCharacterInfo* ownerWidget,
	FItemData itemData,
	AWorldItem* vicinityWorldItemActor)
{
	OwnerWidget				= ownerWidget;
	Inventory				= OwnerWidget->GetPlayerController()->GetControllablePawn()->GetInventoryComponent();
	ItemData				= itemData;
	VicinityWorldItemActor	= vicinityWorldItemActor;

	// ������ �̸� ����
	ItemNameTextBlock->SetText(itemData.ItemName);

	// ������ ���� ����
	ItemCountTextBlock->SetText(FText::FromString(FString::FromInt(itemData.ItemCount)));

}

void UWidgetItemSlot::OnWidgetLeftClicked()
{
	if (IsValid(VicinityWorldItemActor))
	{
		Inventory->AddItem(ItemData);

		// ������ ��Ÿ���� WorldItem ���͸� �����մϴ�.
		VicinityWorldItemActor->Destroy();
		VicinityWorldItemActor = nullptr;
	}
}
