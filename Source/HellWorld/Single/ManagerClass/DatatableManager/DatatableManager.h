#pragma once

#include "CoreMinimal.h"
#include "../../../Interfaces/ManagerClassBase.h"
#include "Engine/DataTable.h"
#include "DatatableManager.generated.h"


UCLASS(Config = DatatablePath)
class HELLWORLD_API UDatatableManager : public UObject, 
    public IManagerClassBase
{
    GENERATED_BODY()

private :
    class UHWGameInstance* GameInst;

    // UDatatableManager 가 관리할 Datatable 애셋을 저장합니다.
    TMap<FString, UDataTable*> Datatables;

    // 장비 아이템 데이터 테이블 경로를 저장할 변수
    UPROPERTY(config)
    FString EquipmentDatatablePath;


public :
    UDatatableManager();
    virtual void InitManagerClass() override;

private :
    // Datatable 을 로드합니다
    void LoadDatatables(FString key, FString assetPath);

public :
    template <typename T>
    T* GetDatatableRow(UDataTable* dataTable, FName rowName)
    {
        // 전달된 데이터 테이블이 nullptr 라면 실행하지 않습니다.
        if (!IsValid(dataTable))
        {
            UE_LOG(LogTemp, Error,
                TEXT("DatatableManager.h :: LINE %d :: param(dataTable) is nullptr"));
            return nullptr;
        }

        FString contextString;
        T* rowData = dataTable->FindRow<T>(rowName, contextString);

        return rowData;
    }


    FORCEINLINE UDataTable * operator[] (FString datatableKey)
    { 
        if (!Datatables.Contains(datatableKey))
            return nullptr;

        return (*Datatables.Find(datatableKey));
    }
};
