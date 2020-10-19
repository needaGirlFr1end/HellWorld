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

	// �÷��̾� ĳ���Ϳ� �߰��� �κ��丮 ������Ʈ�� ��Ÿ���ϴ�.
	UPROPERTY()
	class UInventoryComponent * Inventory;

	// ������ ������ ����
	UPROPERTY()
	FItemData ItemData;

	// ���� Ÿ���� ��Ÿ���ϴ�.
	UPROPERTY()
	EItemSlotType ItemSlotType;

	// �ش� ���� ������ �����ϴ� Widget ��ü
	UPROPERTY()
	class UWidgetCharacterInfo * OwnerWidget;

	// �ش� ���԰� ����� WorldItem ����
	UPROPERTY()
	class AWorldItem* VicinityWorldItemActor;

	// ���� �������� ��Ÿ���ϴ�.
	UPROPERTY()
	bool bCanRecyclable;

public :
	virtual void NativeOnInitialized() override;

private : 
	void FindAllWidget();

protected :
	// ��ư ������ Ŭ���� ȣ��� �޼����Դϴ�.
	virtual void OnWidgetRightClicked() override;

public :
	// ���� ������ �ʱ�ȭ�մϴ�.
	void InitializeSlot(class UWidgetCharacterInfo* ownerWidget, 
		FItemData itemData, EItemSlotType slotType,
		class AWorldItem* vicinityWorldItemActor = nullptr);

	// ���� ���� ���θ� ��Ÿ���� ������ ���� ������ / ������
	FORCEINLINE virtual bool GetCanRecyclable()
	{ return bCanRecyclable; }
	FORCEINLINE virtual void SetCanRecyclable(bool canRecyclable)
	{  bCanRecyclable = canRecyclable; }

	// ������ ������ ����� �� ȣ��Ǵ� �޼���
	FORCEINLINE virtual void OnRecycleStart() override
	{ bCanRecyclable = false; }

private :
	// ��ư ���� Ŭ���� ȣ��� �޼���
	UFUNCTION()
	void OnWidgetLeftClicked();

public :
	// ������ ������ ������ ��ȯ�մϴ�.
	FORCEINLINE const FItemData& GetItemData() const
	{ return ItemData; } 

};
