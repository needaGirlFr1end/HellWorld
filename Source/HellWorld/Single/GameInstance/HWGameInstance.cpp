// Fill out your copyright notice in the Description page of Project Settings.


#include "HWGameInstance.h"
#include "../ManagerClass/DatatableManager/DatatableManager.h"

void UHWGameInstance::Init()
{
	Super::Init();

	RegisterManagerClass<UDatatableManager>();

}

FStreamableManager* UHWGameInstance::GetStreamableManager()
{
	return &UAssetManager::GetStreamableManager();
}
