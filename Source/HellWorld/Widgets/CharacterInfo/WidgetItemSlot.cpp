// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetItemSlot.h"

void UWidgetItemSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	FindAllWidget();
}

void UWidgetItemSlot::FindAllWidget()
{

}


void UWidgetItemSlot::InitializeSlot(
	UWidgetCharacterInfo* ownerWidget,
	FItemData itemData,
	AWorldItem* vicinityWorldItemActor)
{

}