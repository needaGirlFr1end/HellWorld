#pragma once

#include "CoreMinimal.h"
#include "../../Interfaces/ObjectPoolable.h"
#include "ObjectPool.generated.h"

UCLASS()
class HELLWORLD_API UObjectPool : public UObject
{
	GENERATED_BODY()
	
private :
	// Ǯ���� ������Ʈ���� ������ �迭
	TArray<IObjectPoolable*> PoolObjects;

public :
	// ��Ȱ���� ������Ʈ�� �����ϴ��� Ȯ���մϴ�.
	/// - return : ��Ȱ�� ������ ������Ʈ�� �����Ѵٸ� true �� �����մϴ�.
	/// - outFindIndex : ��Ȱ�� ������ ������Ʈ �ε����� ������ ����
	FORCEINLINE bool CheckCanRecycle(int32* outFindIndex = nullptr)
	{
		// ���� ������ ��ü�� �ε����� �����մϴ�.
		int32 findIndex = PoolObjects.FindLastByPredicate(
			[](IObjectPoolable* poolableObject) -> bool
			{ return poolableObject->GetCanRecyclable(); });

		// ���� outFindIndex �� nullptr �� �ƴ� ��� ã�� �ε��� ��ȣ�� �����մϴ�.
		if (outFindIndex != nullptr)
			(*outFindIndex) = findIndex;

		// ���� ������ ��ü�� �����ϴ����� ��ȯ�մϴ�.
		return (findIndex != INDEX_NONE);
	}

	// Ǯ���� ���ο� ������Ʈ�� ����մϴ�.
	template<typename T>
	T* RegisterRecyclableObject(T* newRecyclableObject)
	{
		PoolObjects.Add((IObjectPoolable*)newRecyclableObject);
		return newRecyclableObject;
	}

	// ��Ȱ��� ��ü�� ����ϴ�.
	/// - callOnRecycleStart : ���� ������ ��ü�� ã���� ��� OnRecycleStart() �� ȣ���ų �������� �����մϴ�.
	IObjectPoolable* GetRecycledObject(bool callOnRecycleStart = true);
};

