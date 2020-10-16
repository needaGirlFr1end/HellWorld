#pragma once

#include "HellWorld.h"
#include "Components/ActorComponent.h"

#include "../../Structures/ItemData/ItemData.h"

#include "InventoryComponent.generated.h"


UCLASS()
class HELLWORLD_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

private : 
	class APlayerCharacter* PlayerCharacter;
	class UWidgetCharacterInfo* CharacterInfoWidget;

	// �κ��丮�� �߰��� ������ �����͵�
	TArray<FItemData> InventoryItemDatas;

public:	
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public :
	// �κ��丮�� �������� �߰��մϴ�.
	void AddItem(FItemData itemData);

	// �κ��丮���� �������� �����մϴ�.
	void RemoveItem(FItemData itemData);
		
};
