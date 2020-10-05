#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

UCLASS()
class HELLWORLD_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
private :
	// �÷��̾� ĳ���͸� ��Ÿ���ϴ�.
	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;

protected :
	// ĳ���͸� �������� ĳ������ �̵� ������ �����ϴ� �Է� ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Input")
	FVector XYDirectionInput;

	// ĳ������ �ӷ��� ��Ÿ���ϴ�.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default")
	float OwnerVelocityLength;

	// ĳ���Ͱ� �����θ� �̵��������� ��Ÿ���ϴ�.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character State")
	bool bOnlySideMove;

	// ĳ���Ͱ� ���߿� ���ִ����� ��Ÿ���ϴ�.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character State")
	bool bIsInAir;

	// Bone : Hip �� �߰� ȸ������ ��Ÿ���ϴ�.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bone Trasnform")
	FRotator HipAdditiveRotation;

private :
	// ĳ���Ͱ� �ڷ� �̵��������� ��Ÿ���ϴ�.
	UPROPERTY()
	bool bMoveBackward;


public :
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private :
	// XYDirectionInput ���� ������Ʈ �մϴ�.
	void UpdateXYDirectionInput();

	// Bone ȸ������ ������Ʈ�մϴ�.
	void UpdateBoneRotation(float dt);





};
