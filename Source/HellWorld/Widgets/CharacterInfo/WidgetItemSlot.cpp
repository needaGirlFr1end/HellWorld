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
	EItemSlotType slotType,
	AWorldItem* vicinityWorldItemActor)
{
	OwnerWidget				= ownerWidget;
	Inventory				= OwnerWidget->GetPlayerController()->GetControllablePawn()->GetInventoryComponent();
	ItemSlotType			= slotType;
	ItemData				= itemData;
	VicinityWorldItemActor	= vicinityWorldItemActor;

	// ������ �̸� ����
	ItemNameTextBlock->SetText(itemData.ItemName);

	// ������ ���� ����
	ItemCountTextBlock->SetText(FText::FromString(FString::FromInt(itemData.ItemCount)));

}

void UWidgetItemSlot::OnWidgetLeftClicked()
{
	switch (ItemSlotType)
	{
	case EItemSlotType::IS_Vicinity:
		if (IsValid(VicinityWorldItemActor))
		{
			Inventory->AddItem(ItemData);

			// ������ ��Ÿ���� WorldItem ���͸� �����մϴ�.
			VicinityWorldItemActor->Destroy();
			VicinityWorldItemActor = nullptr;
		}
		break;

	case EItemSlotType::IS_Inventory:
		Inventory->EquipItem(this);
		break;
	}

}

void UWidgetItemSlot::OnWidgetRightClicked()
{
	if (ItemSlotType != EItemSlotType::IS_Inventory) return;

	// �÷��̾� ĳ���� ��ü�� ����ϴ�.
	APlayerCharacter* playerCharacter =
		Cast<APlayerCharacter>(OwnerWidget->GetPlayerController()->GetControllablePawn());

	// ������ ����
	AWorldItem::SpawnWorldItem(
		GetWorld(),
		ItemData.ItemCode,
		ItemData.ItemCount,
		playerCharacter->GetActorLocation(),
		playerCharacter->GetActorRotation());

	// �κ��丮���� �ش� �������� �����մϴ�.
	Inventory->RemoveItem(ItemData);
}