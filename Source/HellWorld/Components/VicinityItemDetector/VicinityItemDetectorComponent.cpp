#include "VicinityItemDetectorComponent.h"

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

	// �ش� ������Ʈ�� ��� ���Ͱ� ������ ��� ȣ���ų �޼��带 �븮�ڿ� ��Ͻ�ŵ�ϴ�.
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

