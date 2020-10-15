// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HellWorld.h"
#include "Blueprint/UserWidget.h"
#include "WidgetCharacterInfo.generated.h"

/**
 * 
 */
UCLASS()
class HELLWORLD_API UWidgetCharacterInfo : public UUserWidget
{
	GENERATED_BODY()

private:

	// ������ �������� ���� ���� Ŭ����
	TSubclassOf<class UWidgetItemSlot> ItemSlotWidgetClass;

	// ������ ��ġ�� �������� ǥ���ϴ� UScollBox
	class UScrollBox* VicinityItemView;

	// ����� �����۵��� ǥ���ϴ� ���� �ν��Ͻ���
	TMap<class AWorldItem*, class UWidgetItemSlot*> VicinityItemSlotInstances;

public :
	UWidgetCharacterInfo(const FObjectInitializer& ObjInitializer);

private :
	void LoadAsset();
	void FindAllWidget();

	// WidgetItemSlot ��ü�� �����Ͽ� ��ȯ�մϴ�.
	class UWidgetItemSlot* CreateItemSlotWidget();

public :
	virtual void NativeOnInitialized() override;

public :
	// ����� �������� ������ ǥ���մϴ�.
	void AddVicinityItemSlot(class AWorldItem* newItem);

	// ����� �������� ǥ���ϴ� ������ �����մϴ�.
	void RemoveVicinityItemSlot(class AWorldItem* newItem);




	
};
