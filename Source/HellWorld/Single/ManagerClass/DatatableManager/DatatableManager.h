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

    // UDatatableManager �� ������ Datatable �ּ��� �����մϴ�.
    TMap<FString, UDataTable*> Datatables;

    // ��� ������ ������ ���̺� ��θ� ������ ����
    UPROPERTY(config)
    FString EquipmentDatatablePath;


public :
    UDatatableManager();
    virtual void InitManagerClass() override;

private :
    // Datatable �� �ε��մϴ�
    void LoadDatatables(FString key, FString assetPath);

public :
    template <typename T>
    T* GetDatatableRow(UDataTable* dataTable, FName rowName)
    {
        // ���޵� ������ ���̺��� nullptr ��� �������� �ʽ��ϴ�.
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
