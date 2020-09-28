#pragma once

#include "HellWorld.h"
#include "GameFramework/Character.h"
#include "../../../Interfaces/PlayerControllable.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class HELLWORLD_API APlayerCharacter : public ACharacter,
	public IPlayerControllable
{
	GENERATED_BODY()

private :
	// 카메라 관련 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent * SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	// 폰을 조종하는 컨트롤러를 나타냅니다.
	UPROPERTY()
	class ATPSPlayerController * PlayerController;

	// 입력 값을 저장할 변수
	UPROPERTY()
	float HorizontalInputAxis;
	UPROPERTY()
	float VerticalInputAxis;

	// 폰이 현재 조종당하는지를 나타내는 변수입니다.
	UPROPERTY()
	bool bIsControlled;


public:
	APlayerCharacter();

#pragma region Character Class Override
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 컨트롤러와 폰이 연결될 경우 호출되는 메서드
	virtual void PossessedBy(AController* NewController) override;

	// 컨트롤러와 폰의 연결이 끊길 경우 호출되는 메서드
	virtual void UnPossessed() override;
#pragma endregion

#pragma region IPlayerControllable Implement
public :
	FORCEINLINE virtual bool IsControlled() const override
	{ return bIsControlled; }

	virtual void OnControllerHorizontalInput(FVector worldDirection, float axis) override;
	virtual void OnControllerVerticalInput(FVector worldDirection, float axis) override;
#pragma endregion

private :
	void InitializeComponents();
	void LoadAsset();

	// 이동중이지 않을 경우 회전을 잠급니다.
	void RotationLock();

public :
	// 입력값 반환
	FORCEINLINE float GetHorizontalInputAxis() const
	{ return HorizontalInputAxis; }
	FORCEINLINE float GetVerticalInputAxis() const
	{ return VerticalInputAxis; }

	// 이동 키가 눌려있는지를 반환
	/// - WSAD 키가 눌려있지 않다면 false 를 리턴
	FORCEINLINE bool IsMoveKeyPressed() const
	{
		return (FMath::Abs(GetHorizontalInputAxis()) > 0.01f) ||
			(FMath::Abs(GetVerticalInputAxis()) > 0.01f);
	}


};
