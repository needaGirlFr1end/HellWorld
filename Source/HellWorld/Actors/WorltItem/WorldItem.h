// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HellWorld.h"
#include "GameFramework/Actor.h"
#include "../../Structures/ItemData/ItemData.h"

#include "WorldItem.generated.h"

UCLASS()
class HELLWORLD_API AWorldItem final : public AActor
{
	GENERATED_BODY()

private :
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ItemMesh;

	// 아이템 개수를 나타냅니다.
	UPROPERTY(EditAnywhere, Category = "Basic Option", meta = (AllowPrivateAccess = "true"))
	int32 ItemCount;

	// 아이템 코드를 나타냅니다.
	/// - 월드에 미리 생성시킬 경우 사용됩니다.
	UPROPERTY(EditAnywhere, Category = "Basic Option", meta = (AllowPrivateAccess = "true"))
	FString ItemCode;

	// 월드에 먼저 배치되어있는 아이템인지를 나타냅니다.
	/// - true 일 경우 ItemCode 에 따라 ItemMesh, ItemInfo 를 로드합니다.
	/// - false 일 경우 해당 액터를 생성한 후, InitializeItemData() 를 호출해야 합니다.
	UPROPERTY(EditAnywhere, Category = "Basic Option", meta = (AllowPrivateAccess = "true"))
	bool bIsWorldItem;

	// 아이템 정보를 나타냅니다.
	FItemData ItemData;

	class UHWGameInstance* GameInst;
	class UDatatableManager* DatatableManager;



	
public:	
	AWorldItem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private :
	void InitializeComponents();
	void OnWorldItemMeshLoaded();

public :
	void InitializeItemData(FString itemCode, int32 itemCount = 1);




};
