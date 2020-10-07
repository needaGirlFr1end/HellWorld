#include "VicinityItemDetectorComponent.h"

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

	// 해당 컴포넌트와 어떠한 액터가 겹쳤을 경우 호출시킬 메서드를 대리자에 등록시킵니다.
	OnComponentBeginOverlap.AddDynamic(
		this, &UVicinityItemDetectorComponent::OnVicinityItemDetected);
}

void UVicinityItemDetectorComponent::OnVicinityItemDetected(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
}

