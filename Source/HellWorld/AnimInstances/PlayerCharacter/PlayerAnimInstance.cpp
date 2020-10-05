#include "PlayerAnimInstance.h"
#include "../../Actors/Characters/PlayerCharacter/PlayerCharacter.h"

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	// 캐릭터 객체를 얻습니다.
	PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// 만약 PlayerCharacter 객체가 유효하지 않다면 하단 구문을 실행하지 않습니다.
	if (!IsValid(PlayerCharacter)) return;

	UpdateXYDirectionInput();

	UpdateBoneRotation(DeltaSeconds);

	// 캐릭터 속력 얻기
	OwnerVelocityLength = PlayerCharacter->GetVelocity().Size();

	// 캐릭터가 점프중인지 확인
	bIsInAir = PlayerCharacter->IsInAir();

	// 캐릭터가 오직 옆으로 이동중인지 확인
	bOnlySideMove = (FMath::Abs(XYDirectionInput.X) < 0.1f &&
		FMath::Abs(XYDirectionInput.Y) > 0.1f);

	// 뒤로 이동중인지 확인
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

	// 목표 Bone : Hip 회전값을 설정합니다.
	float targetHipRotationYaw = XYDirectionInput.Y * maximumHipRotationYaw * 
		(bMoveBackward ? -1.0f : 1.0f);

	// 하체 회전이 부드럽게 이루어질 수 있도록 실제 회전에 적용되는 값을 저장합니다.
	float currentHipRotationYaw = FMath::FInterpTo(
		HipAdditiveRotation.Yaw, targetHipRotationYaw, dt, interpSpeed);

	// Bone : Hip 회전값 설정
	HipAdditiveRotation = FRotator(0.0f, currentHipRotationYaw, 0.0f);
}