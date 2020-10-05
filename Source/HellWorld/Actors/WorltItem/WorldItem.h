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

	// ������ ������ ��Ÿ���ϴ�.
	UPROPERTY(VisibleAnywhere, Category = "Basic Option", meta = (AllowPrivateAccess = "true"))
	int32 ItemCount;

	// ������ �ڵ带 ��Ÿ���ϴ�.
	/// - ���忡 �̸� ������ų ��� ���˴ϴ�.
	UPROPERTY(VisibleAnywhere, Category = "Basic Option", meta = (AllowPrivateAccess = "true"))
	FString ItemCode;

	// ���忡 ���� ��ġ�Ǿ��ִ� ������������ ��Ÿ���ϴ�.
	/// - true �� ��� ItemCode �� ���� ItemMesh, ItemInfo �� �ε��մϴ�.
	/// - false �� ��� �ش� ���͸� ������ ��, InitializeItemData() �� ȣ���ؾ� �մϴ�.
	UPROPERTY(VisibleAnywhere, Category = "Basic Option", meta = (AllowPrivateAccess = "true"))
	bool bIsWorldItem;

	// ������ ������ ��Ÿ���ϴ�.
	FItemData ItemData;

	
public:	
	AWorldItem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private :
	void InitializeComponents();

public :
	void InitializeItemData(FString itemCode, int32 itemCount = 1);


};
