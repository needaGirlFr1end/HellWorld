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

	// 인벤토리에 추가된 아이템 데이터들
	TArray<FItemData> InventoryItemDatas;

public:	
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public :
	// 인벤토리에 아이템을 추가합니다.
	void AddItem(FItemData itemData);

	// 인벤토리에서 아이템을 제거합니다.
	void RemoveItem(FItemData itemData);
		
};
