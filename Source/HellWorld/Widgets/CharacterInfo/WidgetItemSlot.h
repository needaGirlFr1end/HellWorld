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

	// ������ ������ ����
	UPROPERTY()
	FItemData ItemData;

	// �ش� ���� ������ �����ϴ� Widget ��ü
	UPROPERTY()
	class UWidgetCharacterInfo * OwnerWidget;

	// �ش� ���԰� ����� WorldItem ����
	UPROPERTY()
	class AWorldItem* VicinityWorldItemActor;

public :
	virtual void NativeOnInitialized() override;

private : 
	void FindAllWidget();

public :
	// ���� ������ �ʱ�ȭ�մϴ�.
	void InitializeSlot(class UWidgetCharacterInfo* ownerWidget, 
		FItemData itemData, 
		class AWorldItem* vicinityWorldItemActor = nullptr);

private :
	// ��ư ���� Ŭ���� ȣ��� �޼���
	UFUNCTION()
	void OnWidgetLeftClicked();

};
