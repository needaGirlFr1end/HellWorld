// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HellWorld.h"
#include "Engine/GameInstance.h"

#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

#include "../../Interfaces/ManagerClassBase.h"

#include "HWGameInstance.generated.h"

UCLASS()
class HELLWORLD_API UHWGameInstance final : public UGameInstance
{
	GENERATED_BODY()

private :
	// ����� �Ŵ��� Ŭ���� �ν��Ͻ��� ������ �迭
	TArray<IManagerClassBase*> ManagerClasses;

	// �Ŵ��� Ŭ������ �迭�� �߰��մϴ�.
	template<typename T>
	T* RegisterManagerClass()
	{
		IManagerClassBase* managerClassInstance = NewObject<T>(this);
		managerClassInstance->InitManagerClass();
		ManagerClasses.Add(managerClassInstance);

		return Cast<T>(managerClassInstance);
	}

public :
	virtual void Init() override;

	FStreamableManager* GetStreamableManager();

	// ����� �Ŵ��� Ŭ������ ����ϴ�.
	template <typename T>
	T* GetManagerClass()
	{

		// �迭�� �߰��� ��ҵ��� Ȯ���մϴ�.
		for (auto managerInst : ManagerClasses)
		{
			// managerInst �� IManagerClassBase �� ��ġ�ϴ� Ÿ������ Ȯ���մϴ�.
			auto managerInstToReturn = Cast<IManagerClassBase>(managerInst);

			// ���� ��ġ�ϴ� Ÿ���̶�� ����
			if (managerInstToReturn)
				return Cast<T>(managerInstToReturn);
		}

		// ã�� ������ ��� nullptr �� ����
		return nullptr;
	}


	
};
