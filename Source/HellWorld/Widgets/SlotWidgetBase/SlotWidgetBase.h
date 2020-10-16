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
	// ���콺 ��ư�� Ŭ���Ǿ��� ��� ȣ��˴ϴ�.
	virtual FReply NativeOnPreviewMouseButtonDown(
		const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	// ���콺 ������ ��ư Ŭ���� ȣ��Ǵ� �޼���
	virtual void OnWidgetRightClicked() PURE_VIRTUAL(USlotWidgetBase::OnWidgetRightClicked, );

};
