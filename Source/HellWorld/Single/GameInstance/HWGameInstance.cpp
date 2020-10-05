// Fill out your copyright notice in the Description page of Project Settings.


#include "HWGameInstance.h"

void UHWGameInstance::Init()
{
	Super::Init();

}

FStreamableManager* UHWGameInstance::GetStreamableManager()
{
	return &UAssetManager::GetStreamableManager();
}
