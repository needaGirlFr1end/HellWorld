#include "ObjectPool.h"

IObjectPoolable* UObjectPool::GetRecycledObject(bool callOnRecycleStart)
{
	// 재사용 가능한 객체의 인덱스를 저장할 변수
	int32 recycledObjIndex = INDEX_NONE;

	// 만약 재사용 가능한 객체가 존재하지 않는다면 nullptr 를 리턴합니다.
	if (!CheckCanRecycle(&recycledObjIndex)) return nullptr;

	// 만약 callOnRecycleStart 가 참이라면 OnRecycleStart() 까지 호출합니다.
	if (callOnRecycleStart)
		PoolObjects[recycledObjIndex]->OnRecycleStart();

	// 재사용 가능한 객체를 반환합니다.
	return PoolObjects[recycledObjIndex];
}
