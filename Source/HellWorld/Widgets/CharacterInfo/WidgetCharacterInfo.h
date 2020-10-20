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
	// �÷��̾� ��Ʈ�ѷ�
	UPROPERTY()
	class ATPSPlayerController* PlayerController;

	// ������ �������� ���� ���� Ŭ����
	TSubclassOf<class UWidgetItemSlot> ItemSlotWidgetClass;

	// ������ ��ġ�� �������� ǥ���ϴ� ScrollBox
	class UScrollBox* VicinityItemView;

	// ����� �����۵��� ǥ���ϴ� ���� �ν��Ͻ���
	TMap<class AWorldItem*, class UWidgetItemSlot*> VicinityItemSlotInstances;

	// �������� �������� ǥ���ϴ� ScrollBox
	class UScrollBox* InventoryItemView;

	// �κ��丮�� ǥ������ ���Ե�
	TArray<class UWidgetItemSlot*> InventoryItemSlotInstances;

	// �������� ������ ���Ե�
	TArray<class UWidgetEquipItemSlot*> EquipItemSlotInstances;

	// ������ UWidgetItemSlot ��ü���� �����ϰ� ���� Ǯ ��ü
	UPROPERTY()
	UObjectPool* ItemSlotPool;


public :
	UWidgetCharacterInfo(const FObjectInitializer& ObjInitializer);

private :
	void LoadAsset();

	// �������� �������� ǥ���ϴ� ���Ե��� ã���ϴ�.
	void FindEquipItemSlotInstances();
	void FindAllWidget();

	// WidgetItemSlot ��ü�� �����Ͽ� ��ȯ�մϴ�.
	class UWidgetItemSlot* CreateItemSlotWidget();

public :
	virtual void NativeOnInitialized() override;

public :

	// �ʱ�ȭ
	void InitializeCharacterInfoWidget(class ATPSPlayerController* playerController);

	// ����� �������� ������ ǥ���մϴ�.
	void AddVicinityItemSlot(class AWorldItem* newItem);

	// ����� �������� ǥ���ϴ� ������ �����մϴ�.
	void RemoveVicinityItemSlot(class AWorldItem* newItem);

	// �κ��丮 ������ ������Ʈ
	void UpdateInventoryItems(const TArray<FItemData>& itemDatas);

	// ���� ������ ���� ������Ʈ
	void UpdateEquipItem(const TArray<FItemData>& equipItemDatas);


public : 
	FORCEINLINE class ATPSPlayerController* GetPlayerController() const
	{ return PlayerController; }



	
};
