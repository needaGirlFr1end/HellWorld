#include "ObjectPool.h"

IObjectPoolable* UObjectPool::GetRecycledObject(bool callOnRecycleStart)
{
	// ���� ������ ��ü�� �ε����� ������ ����
	int32 recycledObjIndex = INDEX_NONE;

	// ���� ���� ������ ��ü�� �������� �ʴ´ٸ� nullptr �� �����մϴ�.
	if (!CheckCanRecycle(&recycledObjIndex)) return nullptr;

	// ���� callOnRecycleStart �� ���̶�� OnRecycleStart() ���� ȣ���մϴ�.
	if (callOnRecycleStart)
		PoolObjects[recycledObjIndex]->OnRecycleStart();

	// ���� ������ ��ü�� ��ȯ�մϴ�.
	return PoolObjects[recycledObjIndex];
}
