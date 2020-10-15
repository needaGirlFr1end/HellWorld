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
	// ī�޶� ���� ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent * SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	// ����� ������ ���� ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vicinity Item Detector", meta = (AllowPrivateAccess = "true"))
	class UVicinityItemDetectorComponent* VicinityItemDetector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent * Inventory;
#pragma endregion


#pragma region Controller
	// ���� �����ϴ� ��Ʈ�ѷ��� ��Ÿ���ϴ�.
	UPROPERTY()
	class ATPSPlayerController * PlayerController;
#pragma endregion


#pragma region State
	// �Է� ���� ������ ����
	UPROPERTY()
	float HorizontalInputAxis;
	UPROPERTY()
	float VerticalInputAxis;

	// ���� ���� �������ϴ����� ��Ÿ���� �����Դϴ�.
	UPROPERTY()
	bool bIsControlled;

	// �޸��� Ű�� ������ �ִ����� ��Ÿ���ϴ�.
	UPROPERTY()
	bool bRunKeyPressed;

	// ���� �޸����������� ��Ÿ���ϴ�.
	UPROPERTY()
	bool bIsRun;
#pragma endregion

	// �÷��̾� ĳ���� ������ ��Ÿ���ϴ�.
	FPlayerInfo PlayerInfo;

	// �ִϸ��̼� Ŭ����
	TSubclassOf<class UPlayerAnimInstance> PlayerCharacterAnimClass;


public:
	APlayerCharacter();

#pragma region Character Class Override
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ��Ʈ�ѷ��� ���� ����� ��� ȣ��Ǵ� �޼���
	virtual void PossessedBy(AController* NewController) override;

	// ��Ʈ�ѷ��� ���� ������ ���� ��� ȣ��Ǵ� �޼���
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

	// �̵������� ���� ��� ȸ���� ��޴ϴ�.
	void RotationLock();

	// �޸��� ���¸� ������Ʈ�մϴ�.
	void UpdateRunState();

#pragma region Input Bind
private :
	void OnRunKeyPressed();
	void OnRunKeyReleased();
	void OnJumpKeyPressed();
#pragma endregion

public :
	// �Է°� ��ȯ
	FORCEINLINE float GetHorizontalInputAxis() const
	{ return HorizontalInputAxis; }
	FORCEINLINE float GetVerticalInputAxis() const
	{ return VerticalInputAxis; }

	// �̵� Ű�� �����ִ����� ��ȯ
	/// - WSAD Ű�� �������� �ʴٸ� false �� ����
	FORCEINLINE bool IsMoveKeyPressed() const
	{
		return (FMath::Abs(GetHorizontalInputAxis()) > 0.01f) ||
			(FMath::Abs(GetVerticalInputAxis()) > 0.01f);
	}

	// �޸��� ���� ��ȯ
	FORCEINLINE bool IsRun() const
	{ return bIsRun; }

	// ���߿� ������ ���� ��ȯ
	FORCEINLINE bool IsInAir() const
	{ return GetCharacterMovement()->IsFalling(); }

	// �÷��̾� ������ ��ȯ�մϴ�.
	FORCEINLINE const FPlayerInfo* GetPlayerInfo() const
	{ return &PlayerInfo; }

	// �������� ATPSPlayerController ��ü�� ��ȯ�մϴ�.
	FORCEINLINE class ATPSPlayerController* GetPlayerController() const
	{ return PlayerController; }

	// �κ��丮 ������Ʈ�� ��ȯ�մϴ�.
	FORCEINLINE class UInventoryComponent* GetInventoryComponent() const override
	{ return Inventory; }
};
