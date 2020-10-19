#pragma once

#include "CoreMinimal.h"
#include "../../Interfaces/ObjectPoolable.h"
#include "ObjectPool.generated.h"

UCLASS()
class HELLWORLD_API UObjectPool : public UObject
{
	GENERATED_BODY()
	
private :
	// 풀링할 오브젝트들을 저장할 배열
	TArray<IObjectPoolable*> PoolObjects;

public :
	// 재활용할 오브젝트가 존재하는지 확인합니다.
	/// - return : 재활용 가능한 오브젝트가 존재한다면 true 를 리턴합니다.
	/// - outFindIndex : 재활용 가능한 오브젝트 인덱스를 저장할 변수
	FORCEINLINE bool CheckCanRecycle(int32* outFindIndex = nullptr)
	{
		// 재사용 가능한 객체의 인덱스를 저장합니다.
		int32 findIndex = PoolObjects.FindLastByPredicate(
			[](IObjectPoolable* poolableObject) -> bool
			{ return poolableObject->GetCanRecyclable(); });

		// 만약 outFindIndex 가 nullptr 가 아닐 경우 찾은 인덱스 번호를 저장합니다.
		if (outFindIndex != nullptr)
			(*outFindIndex) = findIndex;

		// 재사용 가능한 객체가 존재하는지를 반환합니다.
		return (findIndex != INDEX_NONE);
	}

	// 풀링할 새로운 오브젝트를 등록합니다.
	template<typename T>
	T* RegisterRecyclableObject(T* newRecyclableObject)
	{
		PoolObjects.Add((IObjectPoolable*)newRecyclableObject);
		return newRecyclableObject;
	}

	// 재활용된 객체를 얻습니다.
	/// - callOnRecycleStart : 재사용 가능한 객체를 찾았을 경우 OnRecycleStart() 를 호출시킬 것인지를 결정합니다.
	IObjectPoolable* GetRecycledObject(bool callOnRecycleStart = true);
};

