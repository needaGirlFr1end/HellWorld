#include "PlayerAnimInstance.h"
#include "../../Actors/Characters/PlayerCharacter/PlayerCharacter.h"

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	// ĳ���� ��ü�� ����ϴ�.
	PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// ���� PlayerCharacter ��ü�� ��ȿ���� �ʴٸ� �ϴ� ������ �������� �ʽ��ϴ�.
	if (!IsValid(PlayerCharacter)) return;

	UpdateXYDirectionInput();

	UpdateBoneRotation(DeltaSeconds);

	// ĳ���� �ӷ� ���
	OwnerVelocityLength = PlayerCharacter->GetVelocity().Size();

	// ĳ���Ͱ� ���������� Ȯ��
	bIsInAir = PlayerCharacter->IsInAir();

	// ĳ���Ͱ� ���� ������ �̵������� Ȯ��
	bOnlySideMove = (FMath::Abs(XYDirectionInput.X) < 0.1f &&
		FMath::Abs(XYDirectionInput.Y) > 0.1f);

	// �ڷ� �̵������� Ȯ��
	bMoveBackward = XYDirectionInput.X < 0.0f;

}

void UPlayerAnimInstance::UpdateXYDirectionInput()
{
	XYDirectionInput.X = PlayerCharacter->GetVerticalInputAxis();
	XYDirectionInput.Y = PlayerCharacter->GetHorizontalInputAxis();
}

void UPlayerAnimInstance::UpdateBoneRotation(float dt)
{
	const float maximumHipRotationYaw = 45.0f;
	const float interpSpeed = 15.0f;

	// ��ǥ Bone : Hip ȸ������ �����մϴ�.
	float targetHipRotationYaw = XYDirectionInput.Y * maximumHipRotationYaw * 
		(bMoveBackward ? -1.0f : 1.0f);

	// ��ü ȸ���� �ε巴�� �̷���� �� �ֵ��� ���� ȸ���� ����Ǵ� ���� �����մϴ�.
	float currentHipRotationYaw = FMath::FInterpTo(
		HipAdditiveRotation.Yaw, targetHipRotationYaw, dt, interpSpeed);

	// Bone : Hip ȸ���� ����
	HipAdditiveRotation = FRotator(0.0f, currentHipRotationYaw, 0.0f);
}