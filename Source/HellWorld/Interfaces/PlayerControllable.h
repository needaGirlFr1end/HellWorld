#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerControllable.generated.h"

// 인터페이스 클래스
/// - 서로 관계없는 것들에 대한 시스템이나 장치를 작동시키기 위한 규제 / 규약을 의미합니다.
/// - 보통 Hax A 상속에 사용됩니다.

// Unreal 의 인터페이스 클래스 선언 방법
/// - 1. 프로퍼티 시스템에 존재 여부를 알릴 클래스
///   - 내용이 비어있어야 하며, UINTERFACE(MinimalAPI) 가 선언되어야 합니다.
///     ㄴ MinimalAPI : 클래스의 형태 정보만 나타냄을 의미합니다.
///   - UInterface 를 상속받아야 합니다.
///     U 접두사를 사용하여 선언합니다.
/// - 2. 실제 다른 클래스에서 구현하게 되는 인터페이스 클래스
///   - 인터페이스의 실제 내용을 작성합니다.
///   - I 접두사를 사용하여 선언합니다.




UINTERFACE(MinimalAPI)
class UPlayerControllable : public UInterface
{
	GENERATED_BODY()
};

class HELLWORLD_API IPlayerControllable
{
	GENERATED_BODY()

public:
	// Unreal C++ 에서 인터페이스 멤버 함수는 항상 구현되어 있어야 합니다.
	/// - 구현 방법
	///   - cpp 에서 기본 내용을 작성.
	///   - PURE_VIRTUAL() 매크로를 사용하여 header 에 작성
	///     - 반환 타입 void : PURE_VIRTUAL(ClassType::Method, );
	///     - 반환 타입 not void : PURE_VIRTUAL(ClassType::Method, return value;);

	virtual bool IsControlled() const												PURE_VIRTUAL(IPlayerControllable::IsControlled, return false;);
	virtual void OnControllerHorizontalInput(FVector worldDirection, float axis)	PURE_VIRTUAL(IPlayerControllable::OnControllerHorizontalInput, );
	virtual void OnControllerVerticalInput(FVector worldDirection, float axis)		PURE_VIRTUAL(IPlayerControllable::OnControllerVerticalInput, );

	virtual class UInventoryComponent* GetInventoryComponent() const PURE_VIRTUAL(IPlayerControllable::GetInventoryComponent, return nullptr;);

};
