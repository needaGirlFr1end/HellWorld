#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

UCLASS()
class HELLWORLD_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
private :
	// 플레이어 캐릭터를 나타냅니다.
	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;

protected :
	// 캐릭터를 기준으로 캐릭터의 이동 방향을 결정하는 입력 값
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Input")
	FVector XYDirectionInput;

	// 캐릭터의 속력을 나타냅니다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default")
	float OwnerVelocityLength;

	// 캐릭터가 옆으로만 이동중인지를 나타냅니다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character State")
	bool bOnlySideMove;

	// 캐릭터가 공중에 떠있는지를 나타냅니다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character State")
	bool bIsInAir;

	// Bone : Hip 의 추가 회전값을 나타냅니다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bone Trasnform")
	FRotator HipAdditiveRotation;

private :
	// 캐릭터가 뒤로 이동중인지를 나타냅니다.
	UPROPERTY()
	bool bMoveBackward;


public :
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private :
	// XYDirectionInput 값을 업데이트 합니다.
	void UpdateXYDirectionInput();

	// Bone 회전값을 업데이트합니다.
	void UpdateBoneRotation(float dt);





};
