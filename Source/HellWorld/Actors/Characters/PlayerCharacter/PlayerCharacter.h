#pragma once

#include "HellWorld.h"
#include "GameFramework/Character.h"
#include "../../../Interfaces/PlayerControllable.h"

#include "../../../Structures/PlayerInfo/PlayerInfo.h"

#include "PlayerCharacter.generated.h"

UCLASS()
class HELLWORLD_API APlayerCharacter : public ACharacter,
	public IPlayerControllable
{
	GENERATED_BODY()

private :

#pragma region Components
	// 카메라 관련 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent * SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	// 가까운 아이템 감지 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vicinity Item Detector", meta = (AllowPrivateAccess = "true"))
	class UVicinityItemDetectorComponent* VicinityItemDetector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent * Inventory;
#pragma endregion


#pragma region Controller
	// 폰을 조종하는 컨트롤러를 나타냅니다.
	UPROPERTY()
	class ATPSPlayerController * PlayerController;
#pragma endregion


#pragma region State
	// 입력 값을 저장할 변수
	UPROPERTY()
	float HorizontalInputAxis;
	UPROPERTY()
	float VerticalInputAxis;

	// 폰이 현재 조종당하는지를 나타내는 변수입니다.
	UPROPERTY()
	bool bIsControlled;

	// 달리기 키를 누르고 있는지를 나타냅니다.
	UPROPERTY()
	bool bRunKeyPressed;

	// 현재 달리는중인지를 나타냅니다.
	UPROPERTY()
	bool bIsRun;
#pragma endregion

	// 플레이어 캐릭터 정보를 나타냅니다.
	FPlayerInfo PlayerInfo;

	// 애니메이션 클래스
	TSubclassOf<class UPlayerAnimInstance> PlayerCharacterAnimClass;


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

	// 달리기 상태를 업데이트합니다.
	void UpdateRunState();

#pragma region Input Bind
private :
	void OnRunKeyPressed();
	void OnRunKeyReleased();
	void OnJumpKeyPressed();
#pragma endregion

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

	// 달리기 상태 반환
	FORCEINLINE bool IsRun() const
	{ return bIsRun; }

	// 공중에 떠있음 상태 반환
	FORCEINLINE bool IsInAir() const
	{ return GetCharacterMovement()->IsFalling(); }

	// 플레이어 정보를 반환합니다.
	FORCEINLINE const FPlayerInfo* GetPlayerInfo() const
	{ return &PlayerInfo; }

	// 조종중인 ATPSPlayerController 객체를 반환합니다.
	FORCEINLINE class ATPSPlayerController* GetPlayerController() const
	{ return PlayerController; }

	// 인벤토리 컴포넌트를 반환합니다.
	FORCEINLINE class UInventoryComponent* GetInventoryComponent() const override
	{ return Inventory; }
};
