// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotWidgetBase.h"

FReply USlotWidgetBase::NativeOnPreviewMouseButtonDown(
	const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// ���콺 ������ ��ư�� �Է� �Ǿ��ٸ�
	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		OnWidgetRightClicked();
	}


	return Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
}