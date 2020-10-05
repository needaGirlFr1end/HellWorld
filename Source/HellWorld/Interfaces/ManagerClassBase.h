// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ManagerClassBase.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UManagerClassBase : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HELLWORLD_API IManagerClassBase
{
	GENERATED_BODY()

public:
	virtual void InitManagerClass() PURE_VIRTUAL(IManagerClassBase::InitManagerClass, );
};
