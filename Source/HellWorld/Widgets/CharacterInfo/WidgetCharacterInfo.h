#pragma once

#include "HellWorld.h"
#include "Blueprint/UserWidget.h"
#include "../../Structures/ItemData/ItemData.h"
#include "../../Util/ObjectPool/ObjectPool.h"
#include "WidgetCharacterInfo.generated.h"

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

	// 장착중인 아이템 슬롯들
	TArray<class UWidgetEquipItemSlot*> EquipItemSlotInstances;

	// 생성한 UWidgetItemSlot 객체들을 저장하고 있을 풀 객체
	UPROPERTY()
	UObjectPool* ItemSlotPool;


public :
	UWidgetCharacterInfo(const FObjectInitializer& ObjInitializer);

private :
	void LoadAsset();

	// 장착중인 아이템을 표시하는 슬롯들을 찾습니다.
	void FindEquipItemSlotInstances();
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

	// 장착 아이템 슬롯 업데이트
	void UpdateEquipItem(const TArray<FItemData>& equipItemDatas);


public : 
	FORCEINLINE class ATPSPlayerController* GetPlayerController() const
	{ return PlayerController; }



	
};
