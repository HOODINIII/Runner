// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerCharacter_1.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ARunnerCharacter_1::ARunnerCharacter_1()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	SideViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("SideView Camera"));
	SideViewCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 1.0f;
	GetCharacterMovement()->JumpZVelocity = 900.0f;
	GetCharacterMovement()->GroundFriction = 2.0f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MaxFlySpeed = 500.0f;

	temPos = GetActorLocation();
	zPosition = temPos.Z + 250.0f;


}

// Called when the game starts or when spawned
void ARunnerCharacter_1::BeginPlay()
{
	Super::BeginPlay();
	
	CanMove = true;
}

// Called every frame
void ARunnerCharacter_1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	temPos = GetActorLocation();
	temPos.X -= 850.0f;
	temPos.Z = zPosition;
	SideViewCamera->SetWorldLocation(temPos);
}

// Called to bind functionality to input
void ARunnerCharacter_1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("Move Right / Left", this, &ARunnerCharacter_1::MoveRight);


}

void ARunnerCharacter_1::MoveRight(float value)
{
	if (CanMove)

		AddMovementInput(FVector(0.0f, 1.0f, 0.0f), value);
}

void ARunnerCharacter_1::RestartLevel()
{
}

void ARunnerCharacter_1::OnverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

