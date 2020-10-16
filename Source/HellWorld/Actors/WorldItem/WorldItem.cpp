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
	// 월드에 생성된 아이템이 아니라면 아이템 코드를 설정합니다.
	if (!bIsWorldItem) ItemCode = itemCode;

	// 아이템 정보를 얻기 위하여 아이템 코드를 이용하여 읽어올 Datatable key 를 구합니다.
	FString itemCodeToDatatableKey = FItemData::ItemCodeToDataTableKey(ItemCode);

	UE_LOG(LogTemp, Warning, TEXT("itemCodeToDatatableKey = %s"), *itemCodeToDatatableKey);

	FItemData* itemData = DatatableManager->GetDatatableRow<FItemData>(
		(*DatatableManager)[itemCodeToDatatableKey], FName(*ItemCode));

	if (itemData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("itemData is not loaded!"));
		return;
	}

	// 아이템 정보 설정
	ItemData = *itemData;

	// 아이템 개수 설정
	ItemData.ItemCount = ItemCount = FMath::Clamp(
		itemCount, 1, ItemData.ItemMaxCount);

	GameInst->GetStreamableManager()->RequestAsyncLoad(
		ItemData.WorldStaticMeshPath,
		FStreamableDelegate::CreateUObject(this, &AWorldItem::OnWorldItemMeshLoaded));
}


void AWorldItem::OnWorldItemMeshLoaded()
{
	// 로드된 애셋
	TAssetPtr<UStaticMesh> itemStaticMesh(ItemData.WorldStaticMeshPath);

	if (itemStaticMesh.IsValid())
	{
		ItemMesh->SetStaticMesh(itemStaticMesh.Get());
		ItemMesh->SetSimulatePhysics(true);
	}
}