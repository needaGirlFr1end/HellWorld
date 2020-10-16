// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotWidgetBase.h"

FReply USlotWidgetBase::NativeOnPreviewMouseButtonDown(
	const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// 마우스 오른쪽 버튼이 입력 되었다면
	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		OnWidgetRightClicked();
	}


	return Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
}