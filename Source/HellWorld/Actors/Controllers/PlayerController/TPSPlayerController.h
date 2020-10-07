// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HellWorld.h"
#include "GameFramework/PlayerController.h"
#include "TPSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HELLWORLD_API ATPSPlayerController : public APlayerController
{
	GENERATED_BODY()

private :
	// �������� ���� ��Ÿ���ϴ�.
	class IPlayerControllable* ControllablePawn;

	// ĳ���� ���� Ŭ������ ��Ÿ���ϴ�.
	TSubclassOf<class UWidgetCharacterInfo> CharacterWidgetClass;

	// ĳ���� ���� �ν��Ͻ��� ��Ÿ���ϴ�.
	UPROPERTY()
	class UWidgetCharacterInfo* CharacterWidgetInstance;

	// ĳ���� ������ ǥ�������� Ȯ���մϴ�.
	UPROPERTY()
	bool bActivatedCharacterWidget;

public :
	ATPSPlayerController();

private :
	void LoadAsset();

protected :
	virtual void SetupInputComponent() override;

	// ��Ʈ�ѷ��� ���� ����� �� ȣ��˴ϴ�.
	virtual void OnPossess(APawn* aPawn) override;

private :
	// �⺻ �̵��̳� ȸ���� ���� ���콺, Ű���� �Է½� ȣ��˴ϴ�.
	void InputMouseX(float axis);
	void InputMouseY(float axis);
	void InputHorizontal(float axis);
	void InputVertical(float axis);
	void OpenInfo();

public :
	class UWidgetCharacterInfo* GetCharacterInfoWidgetInstance();
	
};
