#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerControllable.generated.h"

// �������̽� Ŭ����
/// - ���� ������� �͵鿡 ���� �ý����̳� ��ġ�� �۵���Ű�� ���� ���� / �Ծ��� �ǹ��մϴ�.
/// - ���� Hax A ��ӿ� ���˴ϴ�.

// Unreal �� �������̽� Ŭ���� ���� ���
/// - 1. ������Ƽ �ý��ۿ� ���� ���θ� �˸� Ŭ����
///   - ������ ����־�� �ϸ�, UINTERFACE(MinimalAPI) �� ����Ǿ�� �մϴ�.
///     �� MinimalAPI : Ŭ������ ���� ������ ��Ÿ���� �ǹ��մϴ�.
///   - UInterface �� ��ӹ޾ƾ� �մϴ�.
///     U ���λ縦 ����Ͽ� �����մϴ�.
/// - 2. ���� �ٸ� Ŭ�������� �����ϰ� �Ǵ� �������̽� Ŭ����
///   - �������̽��� ���� ������ �ۼ��մϴ�.
///   - I ���λ縦 ����Ͽ� �����մϴ�.




UINTERFACE(MinimalAPI)
class UPlayerControllable : public UInterface
{
	GENERATED_BODY()
};

class HELLWORLD_API IPlayerControllable
{
	GENERATED_BODY()

public:
	// Unreal C++ ���� �������̽� ��� �Լ��� �׻� �����Ǿ� �־�� �մϴ�.
	/// - ���� ���
	///   - cpp ���� �⺻ ������ �ۼ�.
	///   - PURE_VIRTUAL() ��ũ�θ� ����Ͽ� header �� �ۼ�
	///     - ��ȯ Ÿ�� void : PURE_VIRTUAL(ClassType::Method, );
	///     - ��ȯ Ÿ�� not void : PURE_VIRTUAL(ClassType::Method, return value;);

	virtual bool IsControlled() const												PURE_VIRTUAL(IPlayerControllable::IsControlled, return false;);
	virtual void OnControllerHorizontalInput(FVector worldDirection, float axis)	PURE_VIRTUAL(IPlayerControllable::OnControllerHorizontalInput, );
	virtual void OnControllerVerticalInput(FVector worldDirection, float axis)		PURE_VIRTUAL(IPlayerControllable::OnControllerVerticalInput, );

	virtual class UInventoryComponent* GetInventoryComponent() const PURE_VIRTUAL(IPlayerControllable::GetInventoryComponent, return nullptr;);

};
