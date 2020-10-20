#pragma once

#include "CoreMinimal.h"
#include "Widgets/SlotWidgetBase/SlotWidgetBase.h"
#include "WidgetEquipItemSlot.generated.h"

UCLASS()
class HELLWORLD_API UWidgetEquipItemSlot : public USlotWidgetBase
{
	GENERATED_BODY()

private:
	class UTextBlock* ItemNameText;
	class UWidgetCharacterInfo* OwnerWidget;
	int32 EquipSlotIndex;



protected :
	virtual void NativeOnInitialized() override;

private :
	void FindAllWidget();
	
public :
	// Equip Slot 객체를 초기화 하는 메서드
	void InitializeEquipSlot(class UWidgetCharacterInfo* ownerWidget, int32 equipSlotIndex);

	void UpdateSlot();

};
