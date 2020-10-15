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
	class UButton* SlotButton;
	class UImage* SlotLineImage;
	class UTextBlock* ItemNameTextBlock;
	class UTextBlock* ItemCountTextBlock;

	// 슬롯의 아이템 정보
	UPROPERTY()
	FItemData ItemData;

	// 해당 슬롯 위젯을 소유하는 Widget 객체
	UPROPERTY()
	class UWidgetCharacterInfo * OwnerWidget;

	// 해당 슬롯과 연결된 WorldItem 액터
	UPROPERTY()
	class AWorldItem* VicinityWorldItemActor;

public :
	virtual void NativeOnInitialized() override;

private : 
	void FindAllWidget();

public :
	// 슬롯 정보를 초기화합니다.
	void InitializeSlot(class UWidgetCharacterInfo* ownerWidget, 
		FItemData itemData, 
		class AWorldItem* vicinityWorldItemActor = nullptr);

private :
	// 버튼 왼쪽 클릭시 호출될 메서드
	UFUNCTION()
	void OnWidgetLeftClicked();

};
