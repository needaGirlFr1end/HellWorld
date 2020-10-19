// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HellWorld.h"
#include "../SlotWidgetBase/SlotWidgetBase.h"
#include "../../Interfaces/ObjectPoolable.h"

#include "../../Structures/ItemData/ItemData.h"
#include "../../Enums/ItemSlotType.h"

#include "WidgetItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class HELLWORLD_API UWidgetItemSlot : public USlotWidgetBase,
	public IObjectPoolable
{
	GENERATED_BODY()
	
private :
	class UButton* SlotButton;
	class UImage* SlotLineImage;
	class UTextBlock* ItemNameTextBlock;
	class UTextBlock* ItemCountTextBlock;

	// 플레이어 캐릭터에 추가된 인벤토리 컴포넌트를 나타냅니다.
	UPROPERTY()
	class UInventoryComponent * Inventory;

	// 슬롯의 아이템 정보
	UPROPERTY()
	FItemData ItemData;

	// 슬롯 타입을 나타냅니다.
	UPROPERTY()
	EItemSlotType ItemSlotType;

	// 해당 슬롯 위젯을 소유하는 Widget 객체
	UPROPERTY()
	class UWidgetCharacterInfo * OwnerWidget;

	// 해당 슬롯과 연결된 WorldItem 액터
	UPROPERTY()
	class AWorldItem* VicinityWorldItemActor;

	// 재사용 가능함을 나타냅니다.
	UPROPERTY()
	bool bCanRecyclable;

public :
	virtual void NativeOnInitialized() override;

private : 
	void FindAllWidget();

protected :
	// 버튼 오른쪽 클릭시 호출될 메서드입니다.
	virtual void OnWidgetRightClicked() override;

public :
	// 슬롯 정보를 초기화합니다.
	void InitializeSlot(class UWidgetCharacterInfo* ownerWidget, 
		FItemData itemData, EItemSlotType slotType,
		class AWorldItem* vicinityWorldItemActor = nullptr);

	// 재사용 가능 여부를 나타내는 변수에 대한 접근자 / 설정자
	FORCEINLINE virtual bool GetCanRecyclable()
	{ return bCanRecyclable; }
	FORCEINLINE virtual void SetCanRecyclable(bool canRecyclable)
	{  bCanRecyclable = canRecyclable; }

	// 아이템 슬롯이 재사용될 때 호출되는 메서드
	FORCEINLINE virtual void OnRecycleStart() override
	{ bCanRecyclable = false; }

private :
	// 버튼 왼쪽 클릭시 호출될 메서드
	UFUNCTION()
	void OnWidgetLeftClicked();

public :
	// 슬롯의 아이템 정보를 반환합니다.
	FORCEINLINE const FItemData& GetItemData() const
	{ return ItemData; } 

};
