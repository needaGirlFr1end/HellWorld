#include "VicinityItemDetectorComponent.h"

#include "../../Actors\WorldItem/WorldItem.h"
#include "../../Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "../../Actors/Controllers/PlayerController/TPSPlayerController.h"
#include "../../Widgets/CharacterInfo/WidgetCharacterInfo.h"


UVicinityItemDetectorComponent::UVicinityItemDetectorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// �������� �����մϴ�.
	//SetSphereRadius(300.0f);
	/// - �����ڿ��� ȣ���� ��� ������ ���� �� ��.
	SphereRadius = 300.0f;
}


void UVicinityItemDetectorComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());

	// �ش� ������Ʈ�� ��� ���Ͱ� ������ ��� ȣ���ų �޼��带 �븮�ڿ� ��Ͻ�ŵ�ϴ�.
	OnComponentBeginOverlap.AddDynamic(
		this, &UVicinityItemDetectorComponent::OnVicinityItemDetected);

	OnComponentEndOverlap.AddDynamic(
		this, &UVicinityItemDetectorComponent::OnVicinityItemLost);
}


void UVicinityItemDetectorComponent::OnVicinityItemDetected(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	// ��ģ WorldItem ���͸� �����մϴ�.
	AWorldItem* newVicinityItem = Cast<AWorldItem>(OtherActor);

	// ��ģ ���Ͱ� WorldItem �� �ƴ϶�� �������� �ʽ��ϴ�.
	if (!IsValid(newVicinityItem)) return;

	// �̹� �迭�� �߰��� ��ü��� �������� �ʽ��ϴ�.
	if (VicinityItems.Find(newVicinityItem) != INDEX_NONE) return;

	// �迭�� �߰��մϴ�.
	VicinityItems.Add(newVicinityItem);

	// CharacterInfoWidget ��ü �Ҵ�ޱ�
	if (!IsValid(CharacterInfoWidgetInstance))
		CharacterInfoWidgetInstance = 
			PlayerCharacter->GetPlayerController()->GetCharacterInfoWidgetInstance();

	// ������ ���Կ� ǥ���մϴ�.
	CharacterInfoWidgetInstance->AddVicinityItemSlot(newVicinityItem);
}

void UVicinityItemDetectorComponent::OnVicinityItemLost(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex)
{
	// ��ħ�� ���� WorldItem ���͸� �����մϴ�.
	AWorldItem* vicinityItem = Cast<AWorldItem>(OtherActor);

	// ���� ��ģ ���Ͱ� WorldItem �� �ƴ϶�� �������� �ʵ��� �մϴ�.
	if (!IsValid(vicinityItem)) return;

	// ��ģ ���Ͱ� �迭�� �߰����� ���� ���Ͷ�� �������� �ʽ��ϴ�.
	auto vicinityItemIndex = VicinityItems.Find(vicinityItem);
	if (vicinityItemIndex == INDEX_NONE) return;

	// �迭���� �����մϴ�.
	VicinityItems.RemoveAt(vicinityItemIndex);

	// ������ ���Կ��� �����մϴ�.
	CharacterInfoWidgetInstance->RemoveVicinityItemSlot(vicinityItem);
}

