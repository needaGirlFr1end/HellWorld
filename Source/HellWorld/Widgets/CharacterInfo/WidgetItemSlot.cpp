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

	// 버튼 왼쪽 클릭시 호출할 메서드 등록
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

	// 아이템 이름 설정
	ItemNameTextBlock->SetText(itemData.ItemName);

	// 아이템 개수 설정
	ItemCountTextBlock->SetText(FText::FromString(FString::FromInt(itemData.ItemCount)));

}

void UWidgetItemSlot::OnWidgetLeftClicked()
{
	if (IsValid(VicinityWorldItemActor))
	{
		Inventory->AddItem(ItemData);

		// 슬롯이 나타내는 WorldItem 액터를 제거합니다.
		VicinityWorldItemActor->Destroy();
		VicinityWorldItemActor = nullptr;
	}
}
