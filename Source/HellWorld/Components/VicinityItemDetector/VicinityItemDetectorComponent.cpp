#include "VicinityItemDetectorComponent.h"

#include "../../Actors\WorldItem/WorldItem.h"
#include "../../Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "../../Actors/Controllers/PlayerController/TPSPlayerController.h"
#include "../../Widgets/CharacterInfo/WidgetCharacterInfo.h"


UVicinityItemDetectorComponent::UVicinityItemDetectorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// 반지름을 설정합니다.
	//SetSphereRadius(300.0f);
	/// - 생성자에서 호출할 경우 에디터 실행 안 됨.
	SphereRadius = 300.0f;
}


void UVicinityItemDetectorComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());

	// 해당 컴포넌트와 어떠한 액터가 겹쳤을 경우 호출시킬 메서드를 대리자에 등록시킵니다.
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
	// 겹친 WorldItem 액터를 저장합니다.
	AWorldItem* newVicinityItem = Cast<AWorldItem>(OtherActor);

	// 겹친 액터가 WorldItem 이 아니라면 실행하지 않습니다.
	if (!IsValid(newVicinityItem)) return;

	// 이미 배열에 추가된 객체라면 실행하지 않습니다.
	if (VicinityItems.Find(newVicinityItem) != INDEX_NONE) return;

	// 배열에 추가합니다.
	VicinityItems.Add(newVicinityItem);

	// CharacterInfoWidget 객체 할당받기
	if (!IsValid(CharacterInfoWidgetInstance))
		CharacterInfoWidgetInstance = 
			PlayerCharacter->GetPlayerController()->GetCharacterInfoWidgetInstance();

	// 아이템 슬롯에 표시합니다.
	CharacterInfoWidgetInstance->AddVicinityItemSlot(newVicinityItem);
}

void UVicinityItemDetectorComponent::OnVicinityItemLost(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex)
{
	// 겹침이 끝난 WorldItem 액터를 저장합니다.
	AWorldItem* vicinityItem = Cast<AWorldItem>(OtherActor);

	// 만약 겹친 액터가 WorldItem 이 아니라면 실행하지 않도록 합니다.
	if (!IsValid(vicinityItem)) return;

	// 겹친 액터가 배열에 추가되지 않은 액터라면 실행하지 않습니다.
	auto vicinityItemIndex = VicinityItems.Find(vicinityItem);
	if (vicinityItemIndex == INDEX_NONE) return;

	// 배열에서 제거합니다.
	VicinityItems.RemoveAt(vicinityItemIndex);

	// 아이템 슬롯에서 제거합니다.
	CharacterInfoWidgetInstance->RemoveVicinityItemSlot(vicinityItem);
}

