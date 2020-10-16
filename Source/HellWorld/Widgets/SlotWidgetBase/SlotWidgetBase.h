// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HellWorld.h"
#include "Blueprint/UserWidget.h"
#include "SlotWidgetBase.generated.h"


UCLASS(Abstract)
class HELLWORLD_API USlotWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected :
	// 마우스 버튼이 클릭되었을 경우 호출됩니다.
	virtual FReply NativeOnPreviewMouseButtonDown(
		const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	// 마우스 오른쪽 버튼 클릭시 호출되는 메서드
	virtual void OnWidgetRightClicked() PURE_VIRTUAL(USlotWidgetBase::OnWidgetRightClicked, );

};
