// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayerController.h"
#include "../../../Interfaces/PlayerControllable.h"
#include "../../../Widgets/CharacterInfo/WidgetCharacterInfo.h"

ATPSPlayerController::ATPSPlayerController()
{
	LoadAsset();
}

void ATPSPlayerController::LoadAsset()
{
	static ConstructorHelpers::FClassFinder<UWidgetCharacterInfo> WIDGETBP_CHARACTER(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/WidgetBP_CharacterInfo.WidgetBP_CharacterInfo_C'"));
	if (WIDGETBP_CHARACTER.Succeeded())
		CharacterWidgetClass = WIDGETBP_CHARACTER.Class;
}


void ATPSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(TEXT("MouseX"), this, &ATPSPlayerController::InputMouseX);
	InputComponent->BindAxis(TEXT("MouseY"), this, &ATPSPlayerController::InputMouseY);

	InputComponent->BindAxis(TEXT("Horizontal"), this, &ATPSPlayerController::InputHorizontal);
	InputComponent->BindAxis(TEXT("Vertical"), this, &ATPSPlayerController::InputVertical);

	InputComponent->BindAction(TEXT("OpenInfo"), EInputEvent::IE_Pressed, this, &ATPSPlayerController::OpenInfo);
}

void ATPSPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	ControllablePawn = Cast<IPlayerControllable>(aPawn);
}

void ATPSPlayerController::InputMouseX(float axis)
{
	AddYawInput(axis);
}

void ATPSPlayerController::InputMouseY(float axis)
{
	AddPitchInput(axis);
}

void ATPSPlayerController::InputHorizontal(float axis)
{
	if (ControllablePawn == nullptr) return;

	// 컨트롤러 회전중 yaw 회전만을 저장합니다.
	FRotator yawRotation = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);

	// 컨트롤러 기준 오른쪽 방향을 저장합니다.
	FVector rightVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
	/// - FRotationMatrix : 회전된 좌표계 정보를 저장하는 행렬을 나타냅니다.
	///   생성자 인수에 회전값을 전달하면 캐릭터의 중심이 (0, 0, 0) 인 상태에서
	///   각 축에 따라 얼마나 회전되어 있는지를 나타내게 됩니다.
	/// - GetUnitAxis(EAxis) : EAxis 축으로의 방향을 반환합니다.

	ControllablePawn->OnControllerHorizontalInput(rightVector, axis);
}

void ATPSPlayerController::InputVertical(float axis)
{
	if (ControllablePawn == nullptr) return;

	// 컨트롤러 회전중 Yaw 회전만을 저장합니다.
	FRotator yawRotation = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);

	// 컨트롤러 기준 앞 방향을 저장합니다.
	FVector forwardVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);

	ControllablePawn->OnControllerVerticalInput(forwardVector, axis);
}

void ATPSPlayerController::OpenInfo()
{
	// CharacterInfoWidget 이 활성화중이라면
	if (bActivatedCharacterWidget)
	{
		// 위젯 비활성화 상태로 설정합니다.
		bActivatedCharacterWidget = false;

		// 마우스 커서를 숨깁니다.
		bShowMouseCursor = false;

		// 위젯을 화면에서 탈착시킵니다.
		GetCharacterInfoWidgetInstance()->RemoveFromParent();

		// 게임 입력만 받도록 합니다.
		SetInputMode(FInputModeGameOnly());
	}
	// CharacterInfoWidget 이 비활성화중이라면
	else
	{
		// 위젯 활성화 상태로 설정합니다.
		bActivatedCharacterWidget = true;

		// 마우스 커서를 표시합니다.
		bShowMouseCursor = true;

		// 위젯을 화면에 부착시킵니다.
		GetCharacterInfoWidgetInstance()->AddToViewport();

		// 게임, UI 입력을 동시에 받도록 합니다.
		SetInputMode(FInputModeGameAndUI());
	}

}

UWidgetCharacterInfo* ATPSPlayerController::GetCharacterInfoWidgetInstance()
{
	if (!IsValid(CharacterWidgetInstance))
	{
		CharacterWidgetInstance = CreateWidget<UWidgetCharacterInfo>(this, CharacterWidgetClass);
		CharacterWidgetInstance->InitializeCharacterInfoWidget(this);
	}

	return CharacterWidgetInstance;
}