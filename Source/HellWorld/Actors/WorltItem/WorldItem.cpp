#include "WorldItem.h"

AWorldItem::AWorldItem()
{
	PrimaryActorTick.bCanEverTick = true;

	InitializeComponents();
}


void AWorldItem::BeginPlay()
{
	Super::BeginPlay();

	if (bIsWorldItem)
		InitializeItemData(ItemCode, ItemCount);
}


void AWorldItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AWorldItem::InitializeComponents()
{
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ITEM_MESH"));
	SetRootComponent(ItemMesh);
}


void AWorldItem::InitializeItemData(FString itemCode, int32 itemCount)
{

}