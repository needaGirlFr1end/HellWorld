#include "PlayerCharacter.h"
#include "../../Controllers/PlayerController/TPSPlayerController.h"
#include "../../../AnimInstances/PlayerCharacter/PlayerAnimInstance.h"

#include "../../../Components/VicinityItemDetector/VicinityItemDetectorComponent.h"

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

	PlayerInfo.Initialize();
}


void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotationLock();
	UpdateRunState();
}


void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed,
		this, &APlayerCharacter::OnRunKeyPressed);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released,
		this, &APlayerCharacter::OnRunKeyReleased);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed,
		this, &APlayerCharacter::OnJumpKeyPressed);
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

#pragma region Camera Settings...
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRING_ARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA_COMPONENT"));

	SpringArm->SetupAttachment(GetRootComponent());
	Camera->SetupAttachment(SpringArm);

	// 컨트롤러 yaw 회전에 맞춰 SpringArm 이 회전하도록 합니다.
	SpringArm->bUsePawnControlRotation = true;

	// 컨트롤러 yaw 회전에 맞춰 캐릭터가 회전하지 않도록 합니다.
	bUseControllerRotationYaw = false;
#pragma endregion

#pragma region Vicinity ItemDetecter Component Settings...
	VicinityItemDetector = CreateDefaultSubobject<UVicinityItemDetectorComponent>(TEXT("VICINITY_ITEM_DETECTOR"));
	VicinityItemDetector->SetupAttachment(GetRootComponent());
#pragma endregion




#pragma region Animation Settings...
	if (IsValid(PlayerCharacterAnimClass))
	{
		GetMesh()->SetAnimInstanceClass(PlayerCharacterAnimClass);
	}
#pragma endregion


}


void APlayerCharacter::LoadAsset()
{
	static ConstructorHelpers::FClassFinder<UPlayerAnimInstance> PLAYER_ANIM_INSTANCE(
		TEXT("AnimBlueprint'/Game/Resources/Blueprints/Characters/PlayerCharacter/AnimBP_PlayerCharacter.AnimBP_PlayerCharacter_C'"));
	if (PLAYER_ANIM_INSTANCE.Succeeded())
		PlayerCharacterAnimClass = PLAYER_ANIM_INSTANCE.Class;
	else { UE_LOG(LogTemp, Error, TEXT("PLAYER_ANIM_INSTANCE is not loaded!")); }
}


void APlayerCharacter::RotationLock()
{
	// 점프중이 아닐 때, 이동 키가 눌렸다면 캐릭터를 컨트롤러 회전값으로 
	// 부드럽게 회전시킵니다.
	GetCharacterMovement()->bUseControllerDesiredRotation = 
		IsMoveKeyPressed() && !IsInAir();
}


void APlayerCharacter::UpdateRunState()
{
	// 달리기 상태 설정
	bIsRun = (bRunKeyPressed && VerticalInputAxis > 0.5f);

	// 이동 속력을 설정합니다.
	/// - 달리기 상태라면 ? RunSpeed : WalkSpeed
	GetCharacterMovement()->MaxWalkSpeed = bIsRun ?
		GetPlayerInfo()->RunSpeed : GetPlayerInfo()->WalkSpeed;
}


#pragma region Input Bind

void APlayerCharacter::OnRunKeyPressed()
{
	// 달리기 키 눌림 상태로 변경
	bRunKeyPressed = true;

}

void APlayerCharacter::OnRunKeyReleased()
{
	// 달리기 키 떼어짐 상태로 변경
	bRunKeyPressed = false;
}

void APlayerCharacter::OnJumpKeyPressed()
{
	// 점프
	Jump();
}

#pragma endregion
