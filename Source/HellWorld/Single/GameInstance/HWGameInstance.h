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
	// 등록한 매니저 클래스 인스턴스를 저장할 배열
	TArray<IManagerClassBase*> ManagerClasses;

	// 매니저 클래스를 배열에 추가합니다.
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

	// 등록한 매니저 클래스를 얻습니다.
	template <typename T>
	T* GetManagerClass()
	{

		// 배열에 추가된 요소들을 확인합니다.
		for (auto managerInst : ManagerClasses)
		{
			// managerInst 가 IManagerClassBase 와 일치하는 타입인지 확인합니다.
			auto managerInstToReturn = Cast<IManagerClassBase>(managerInst);

			// 만약 일치하는 타입이라면 리턴
			if (managerInstToReturn)
				return Cast<T>(managerInstToReturn);
		}

		// 찾지 못했을 경우 nullptr 를 리턴
		return nullptr;
	}


	
};
