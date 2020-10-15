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

	// ��Ʈ�ѷ� ȸ���� yaw ȸ������ �����մϴ�.
	FRotator yawRotation = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);

	// ��Ʈ�ѷ� ���� ������ ������ �����մϴ�.
	FVector rightVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
	/// - FRotationMatrix : ȸ���� ��ǥ�� ������ �����ϴ� ����� ��Ÿ���ϴ�.
	///   ������ �μ��� ȸ������ �����ϸ� ĳ������ �߽��� (0, 0, 0) �� ���¿���
	///   �� �࿡ ���� �󸶳� ȸ���Ǿ� �ִ����� ��Ÿ���� �˴ϴ�.
	/// - GetUnitAxis(EAxis) : EAxis �������� ������ ��ȯ�մϴ�.

	ControllablePawn->OnControllerHorizontalInput(rightVector, axis);
}

void ATPSPlayerController::InputVertical(float axis)
{
	if (ControllablePawn == nullptr) return;

	// ��Ʈ�ѷ� ȸ���� Yaw ȸ������ �����մϴ�.
	FRotator yawRotation = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);

	// ��Ʈ�ѷ� ���� �� ������ �����մϴ�.
	FVector forwardVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);

	ControllablePawn->OnControllerVerticalInput(forwardVector, axis);
}

void ATPSPlayerController::OpenInfo()
{
	// CharacterInfoWidget �� Ȱ��ȭ���̶��
	if (bActivatedCharacterWidget)
	{
		// ���� ��Ȱ��ȭ ���·� �����մϴ�.
		bActivatedCharacterWidget = false;

		// ���콺 Ŀ���� ����ϴ�.
		bShowMouseCursor = false;

		// ������ ȭ�鿡�� Ż����ŵ�ϴ�.
		GetCharacterInfoWidgetInstance()->RemoveFromParent();

		// ���� �Է¸� �޵��� �մϴ�.
		SetInputMode(FInputModeGameOnly());
	}
	// CharacterInfoWidget �� ��Ȱ��ȭ���̶��
	else
	{
		// ���� Ȱ��ȭ ���·� �����մϴ�.
		bActivatedCharacterWidget = true;

		// ���콺 Ŀ���� ǥ���մϴ�.
		bShowMouseCursor = true;

		// ������ ȭ�鿡 ������ŵ�ϴ�.
		GetCharacterInfoWidgetInstance()->AddToViewport();

		// ����, UI �Է��� ���ÿ� �޵��� �մϴ�.
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