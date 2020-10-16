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
	// ������ ������ �߰��մϴ�.
	InventoryItemDatas.Add(itemData);

	// UI �� ǥ���մϴ�.
	CharacterInfoWidget->UpdateInventoryItems(InventoryItemDatas);

}

void UInventoryComponent::RemoveItem(FItemData itemData)
{
	// InventoryItemDatas �迭���� itemData ��ġ�ϴ� ����� �ε����� �����մϴ�.
	int32 inventorySlotIndex = InventoryItemDatas.Find(itemData);
	/// - TArray.Find() �� ���� �������� ���Ŀ��� == �����ڰ� �����ε� �Ǿ��־�� �մϴ�.

	if (inventorySlotIndex == INDEX_NONE) return;

	// inventorySlotIndex �� ��ġ�ϴ� �ε����� ���� ��Ҹ� �����մϴ�.
	InventoryItemDatas.RemoveAt(inventorySlotIndex);

	// ������ ����� ������ ������Ʈ �մϴ�.
	CharacterInfoWidget->UpdateInventoryItems(InventoryItemDatas);
}