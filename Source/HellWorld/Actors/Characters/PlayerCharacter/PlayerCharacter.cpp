#include "PlayerCharacter.h"
#include "../../Controllers/PlayerController/TPSPlayerController.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// 애셋 로드
	LoadAsset();

	// 사용되는 컴포넌트 초기화
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
	// 컨트롤러 기준 왼쪽 / 오른쪽으로 이동시킵니다.
	AddMovementInput(worldDirection, HorizontalInputAxis = axis);

}

void APlayerCharacter::OnControllerVerticalInput(
	FVector worldDirection, float axis)
{
	// 컨트롤러 기준 앞 / 뒤쪽으로 이동시킵니다.
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

	// 컨트롤러 yaw 회전에 맞춰 SpringArm 이 회전하도록 합니다.
	SpringArm->bUsePawnControlRotation = true;

	// 컨트롤러 yaw 회전에 맞춰 캐릭터가 회전하지 않도록 합니다.
	bUseControllerRotationYaw = false;
}


void APlayerCharacter::LoadAsset()
{

}


void APlayerCharacter::RotationLock()
{
	// 이동 키가 눌렸다면 캐릭터를 컨트롤러 회전값으로 부드럽게 회전시킵니다.
	GetCharacterMovement()->bUseControllerDesiredRotation = IsMoveKeyPressed();
}
