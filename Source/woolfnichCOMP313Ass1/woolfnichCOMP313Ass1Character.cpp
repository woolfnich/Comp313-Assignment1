// Copyright Epic Games, Inc. All Rights Reserved.

#include "woolfnichCOMP313Ass1Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AwoolfnichCOMP313Ass1Character::AwoolfnichCOMP313Ass1Character()
{
	didAttack = false;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AwoolfnichCOMP313Ass1Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AwoolfnichCOMP313Ass1Character::JumpAttack);
	PlayerInputComponent->BindAxis("MoveRight", this, &AwoolfnichCOMP313Ass1Character::MoveRight);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AwoolfnichCOMP313Ass1Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AwoolfnichCOMP313Ass1Character::TouchStopped);
}

void AwoolfnichCOMP313Ass1Character::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}


void AwoolfnichCOMP313Ass1Character::JumpAttack() {
	if (GetCharacterMovement()->IsFalling() && !this->didAttack) {
		if (GetActorForwardVector().Y < 0.f) {
			LaunchCharacter(FVector(0.f, -2000.f, 0.f), true, false);
		}
		else {
			LaunchCharacter(FVector(0.f, 2000.f, 0.f), true, false);
		}
		this->didAttack = true;
	}
}

void AwoolfnichCOMP313Ass1Character::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void AwoolfnichCOMP313Ass1Character::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void AwoolfnichCOMP313Ass1Character::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (!GetCharacterMovement()->IsFalling() && this->didAttack) {
		this->didAttack = false;
	}
}
