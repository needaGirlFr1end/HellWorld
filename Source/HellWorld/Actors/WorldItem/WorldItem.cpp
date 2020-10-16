#include "WorldItem.h"

#include "../../Single/GameInstance/HWGameInstance.h"
#include "../../Single/ManagerClass/DatatableManager/DatatableManager.h"


AWorldItem::AWorldItem()
{
	PrimaryActorTick.bCanEverTick = true;

	InitializeComponents();
}


void AWorldItem::BeginPlay()
{
	Super::BeginPlay();

	GameInst = Cast<UHWGameInstance>(GetGameInstance());
	DatatableManager = GameInst->GetManagerClass<UDatatableManager>();

	if (bIsWorldItem)
		InitializeItemData(ItemCode, ItemCount);

	ItemMesh->SetCollisionProfileName(TEXT("WorldItem"));
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


AWorldItem* AWorldItem::SpawnWorldItem(UWorld* world, 
	FString itemCode, int32 itemCount, 
	FVector spawnLocation, FRotator spawnRotation)
{
	AWorldItem* worldItem = world->SpawnActor<AWorldItem>();

	worldItem->SetActorLocationAndRotation(spawnLocation, spawnRotation);
	worldItem->InitializeItemData(itemCode, itemCount);

	return worldItem;
}

void AWorldItem::InitializeItemData(FString itemCode, int32 itemCount)
{
	// ���忡 ������ �������� �ƴ϶�� ������ �ڵ带 �����մϴ�.
	if (!bIsWorldItem) ItemCode = itemCode;

	// ������ ������ ��� ���Ͽ� ������ �ڵ带 �̿��Ͽ� �о�� Datatable key �� ���մϴ�.
	FString itemCodeToDatatableKey = FItemData::ItemCodeToDataTableKey(ItemCode);

	UE_LOG(LogTemp, Warning, TEXT("itemCodeToDatatableKey = %s"), *itemCodeToDatatableKey);

	FItemData* itemData = DatatableManager->GetDatatableRow<FItemData>(
		(*DatatableManager)[itemCodeToDatatableKey], FName(*ItemCode));

	if (itemData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("itemData is not loaded!"));
		return;
	}

	// ������ ���� ����
	ItemData = *itemData;

	// ������ ���� ����
	ItemData.ItemCount = ItemCount = FMath::Clamp(
		itemCount, 1, ItemData.ItemMaxCount);

	GameInst->GetStreamableManager()->RequestAsyncLoad(
		ItemData.WorldStaticMeshPath,
		FStreamableDelegate::CreateUObject(this, &AWorldItem::OnWorldItemMeshLoaded));
}


void AWorldItem::OnWorldItemMeshLoaded()
{
	// �ε�� �ּ�
	TAssetPtr<UStaticMesh> itemStaticMesh(ItemData.WorldStaticMeshPath);

	if (itemStaticMesh.IsValid())
	{
		ItemMesh->SetStaticMesh(itemStaticMesh.Get());
		ItemMesh->SetSimulatePhysics(true);
	}
}