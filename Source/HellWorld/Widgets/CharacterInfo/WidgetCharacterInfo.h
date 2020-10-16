// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HellWorld.h"
#include "Blueprint/UserWidget.h"
#include "../../Structures/ItemData/ItemData.h"
#include "WidgetCharacterInfo.generated.h"

/**
 * 
 */
UCLASS()
class HELLWORLD_API UWidgetCharacterInfo : public UUserWidget
{
	GENERATED_BODY()

private:
	// 플레이어 컨트롤러
	UPROPERTY()
	class ATPSPlayerController* PlayerController;

	// 아이템 슬롯으로 사용될 위젯 클래스
	TSubclassOf<class UWidgetItemSlot> ItemSlotWidgetClass;

	// 가까이 위치한 아이템을 표시하는 ScrollBox
	class UScrollBox* VicinityItemView;

	// 가까운 아이템들을 표시하는 슬롯 인스턴스들
	TMap<class AWorldItem*, class UWidgetItemSlot*> VicinityItemSlotInstances;

	// 소지중인 아이템을 표시하는 ScrollBox
	class UScrollBox* InventoryItemView;

	// 인벤토리에 표시중인 슬롯들
	TArray<class UWidgetItemSlot*> InventoryItemSlotInstances;


public :
	UWidgetCharacterInfo(const FObjectInitializer& ObjInitializer);

private :
	void LoadAsset();
	void FindAllWidget();

	// WidgetItemSlot 객체를 생성하여 반환합니다.
	class UWidgetItemSlot* CreateItemSlotWidget();

public :
	virtual void NativeOnInitialized() override;

public :

	// 초기화
	void InitializeCharacterInfoWidget(class ATPSPlayerController* playerController);

	// 가까운 아이템을 위젯에 표시합니다.
	void AddVicinityItemSlot(class AWorldItem* newItem);

	// 가까운 아이템을 표시하는 위젯을 제거합니다.
	void RemoveVicinityItemSlot(class AWorldItem* newItem);

	// 인벤토리 아이템 업데이트
	void UpdateInventoryItems(const TArray<FItemData>& itemDatas);


public : 
	FORCEINLINE class ATPSPlayerController* GetPlayerController() const
	{ return PlayerController; }



	
};
