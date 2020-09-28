// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	// 조종중인 폰을 나타냅니다.
	class IPlayerControllable* ControllablePawn;

protected :
	virtual void SetupInputComponent() override;

	// 컨트롤러와 폰이 연결될 때 호출됩니다.
	virtual void OnPossess(APawn* aPawn) override;

private :
	// 기본 이동이나 회전에 대한 마우스, 키보드 입력시 호출됩니다.
	void InputMouseX(float axis);
	void InputMouseY(float axis);
	void InputHorizontal(float axis);
	void InputVertical(float axis);
	
};
