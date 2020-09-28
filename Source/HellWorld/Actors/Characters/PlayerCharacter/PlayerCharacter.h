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
	// ī�޶� ���� ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent * SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	// ���� �����ϴ� ��Ʈ�ѷ��� ��Ÿ���ϴ�.
	UPROPERTY()
	class ATPSPlayerController * PlayerController;

	// �Է� ���� ������ ����
	UPROPERTY()
	float HorizontalInputAxis;
	UPROPERTY()
	float VerticalInputAxis;

	// ���� ���� �������ϴ����� ��Ÿ���� �����Դϴ�.
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


};
