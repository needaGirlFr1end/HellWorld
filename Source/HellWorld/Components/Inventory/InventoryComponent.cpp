#include "InventoryComponent.h"

#include "../../Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "../../Actors/Controllers/PlayerController/TPSPlayerController.h"
#include "../../Widgets/CharacterInfo/WidgetCharacterInfo.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	CharacterInfoWidget = PlayerCharacter->GetPlayerController()->GetCharacterInfoWidgetInstance();
}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventoryComponent::AddItem(FItemData itemData)
{
	// 아이템 정보를 추가합니다.
	InventoryItemDatas.Add(itemData);

	// UI 에 표시합니다.
	CharacterInfoWidget->UpdateInventoryItems(InventoryItemDatas);

}

void UInventoryComponent::RemoveItem(FItemData itemData)
{
	// InventoryItemDatas 배열에서 itemData 일치하는 요소의 인덱스를 저장합니다.
	int32 inventorySlotIndex = InventoryItemDatas.Find(itemData);
	/// - TArray.Find() 로 사용될 데이터의 형식에는 == 연산자가 오버로드 되어있어야 합니다.

	if (inventorySlotIndex == INDEX_NONE) return;

	// inventorySlotIndex 와 일치하는 인덱스를 갖는 요소를 제거합니다.
	InventoryItemDatas.RemoveAt(inventorySlotIndex);

	// 위젯에 변경된 정보를 업데이트 합니다.
	CharacterInfoWidget->UpdateInventoryItems(InventoryItemDatas);
}