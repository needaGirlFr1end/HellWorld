// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HellWorld.h"
#include "Blueprint/UserWidget.h"

#include "../../Structures/ItemData/ItemData.h"

#include "WidgetItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class HELLWORLD_API UWidgetItemSlot : public UUserWidget
{
	GENERATED_BODY()
	
private :
	class UImage* SlotLineImage;
	class UTextBlock* ItemNameTextBlock;
	class UTextBlock* ItemCountTextBlock;
	class UButton* SlotButton;

public :
	virtual void NativeOnInitialized() override;

private : 
	void FindAllWidget();

public :
	// 슬롯 정보를 초기화합니다.
	void InitializeSlot(class UWidgetCharacterInfo* ownerWidget, 
		FItemData itemData, 
		class AWorldItem* vicinityWorldItemActor = nullptr);

};
