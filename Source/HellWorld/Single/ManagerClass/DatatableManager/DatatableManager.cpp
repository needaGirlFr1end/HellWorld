#include "DatatableManager.h"
#include "../../GameInstance/HWGameInstance.h"

UDatatableManager::UDatatableManager()
{
}

void UDatatableManager::InitManagerClass()
{
	GameInst = Cast<UHWGameInstance>(GetWorld()->GetGameInstance());

	LoadDatatables(EQUIP, EquipmentDatatablePath);
}

void UDatatableManager::LoadDatatables(FString key, FString assetPath)
{
	TSoftObjectPtr<UDataTable> loadedDatatable = Cast<UDataTable>(
		GameInst->GetStreamableManager()->LoadSynchronous(
			FSoftObjectPath(assetPath)));

	UDataTable* dataTable = loadedDatatable.Get();

	if (IsValid(dataTable))
		Datatables.Add(key, dataTable);
	else
	{
		UE_LOG(LogTemp, Error,
			TEXT("DatatableManager.cpp :: LINE %d :: dataTable is not loaded!"),
			__LINE__);
	}
}
