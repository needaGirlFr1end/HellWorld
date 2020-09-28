#include "PlayerCharacter.h"
#include "../../Controllers/PlayerController/TPSPlayerController.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// �ּ� �ε�
	LoadAsset();

	// ���Ǵ� ������Ʈ �ʱ�ȭ
	InitializeComponents();
}


#pragma region Character Class Override
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotationLock();
}


void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	PlayerController = Cast<ATPSPlayerController>(NewController);
	bIsControlled = true;
}


void APlayerCharacter::UnPossessed()
{
	Super::UnPossessed();

	PlayerController = nullptr;
	bIsControlled = false;
}
#pragma endregion


#pragma region IPlayerControllable Implement
void APlayerCharacter::OnControllerHorizontalInput(
	FVector worldDirection, float axis)
{
	// ��Ʈ�ѷ� ���� ���� / ���������� �̵���ŵ�ϴ�.
	AddMovementInput(worldDirection, HorizontalInputAxis = axis);

}

void APlayerCharacter::OnControllerVerticalInput(
	FVector worldDirection, float axis)
{
	// ��Ʈ�ѷ� ���� �� / �������� �̵���ŵ�ϴ�.
	AddMovementInput(worldDirection, VerticalInputAxis = axis);
}
#pragma endregion


void APlayerCharacter::InitializeComponents()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BASE(
		TEXT("SkeletalMesh'/Game/Resources/Characters/PlayerCharacter/Base/BaseBody.BaseBody'"));
	if (SK_BASE.Succeeded()) GetMesh()->SetSkeletalMesh(SK_BASE.Object);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRING_ARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA_COMPONENT"));

	SpringArm->SetupAttachment(GetRootComponent());
	Camera->SetupAttachment(SpringArm);

	// ��Ʈ�ѷ� yaw ȸ���� ���� SpringArm �� ȸ���ϵ��� �մϴ�.
	SpringArm->bUsePawnControlRotation = true;

	// ��Ʈ�ѷ� yaw ȸ���� ���� ĳ���Ͱ� ȸ������ �ʵ��� �մϴ�.
	bUseControllerRotationYaw = false;
}


void APlayerCharacter::LoadAsset()
{

}


void APlayerCharacter::RotationLock()
{
	// �̵� Ű�� ���ȴٸ� ĳ���͸� ��Ʈ�ѷ� ȸ�������� �ε巴�� ȸ����ŵ�ϴ�.
	GetCharacterMovement()->bUseControllerDesiredRotation = IsMoveKeyPressed();
}
