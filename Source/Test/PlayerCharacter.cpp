// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	MovementArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));

	RootComponent = SceneComponent;
	StaticMeshComponent->SetupAttachment(SceneComponent);
	SpringArm->SetupAttachment(StaticMeshComponent);
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	MovementArrow->SetupAttachment(Camera);

	SpringArm->bUsePawnControlRotation = true;
	StaticMeshComponent->SetSimulatePhysics(true);
	MovementArrow->SetHiddenInGame(false);
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	Speed = 500.0f;
	Values = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};
	CubeValue = 2;
	Tags.Add("Player");
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(FName("MoveForwardBackwards"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveLeftRight"), this, &APlayerCharacter::MoveLeftRight);
	PlayerInputComponent->BindAxis(FName("TurnLeftRight"), this, &APlayerCharacter::TurnLeftRight);
	PlayerInputComponent->BindAxis(FName("TurnUpDown"), this, &APlayerCharacter::TurnUpDown);
}

void APlayerCharacter::MoveForward(float Value)
{
	FVector ForceVector = Camera->GetForwardVector();
	ForceVector.X *= Value * Speed;
	ForceVector.Y *= Value * Speed;
	StaticMeshComponent->AddForce(ForceVector, TEXT("None"), true);
	MovementArrow->SetArrowLength(FMath::Clamp(40.0,StaticMeshComponent->GetPhysicsLinearVelocity().X * 0.5, 60.0));
	MovementArrow->SetWorldRotation(FRotationMatrix::MakeFromX(StaticMeshComponent->GetPhysicsLinearVelocity().GetSafeNormal().RotateAngleAxis(90.0f, FVector::UpVector)).Rotator());
}

void APlayerCharacter::MoveLeftRight(float Value)
{
	FVector ForceVector = Camera->GetRightVector();
	ForceVector.X *= Value * Speed;
	ForceVector.Y *= Value * Speed;
	StaticMeshComponent->AddForce(ForceVector, TEXT("None"), true);
	MovementArrow->SetArrowLength(FMath::Clamp(40.0,FMath::Abs(StaticMeshComponent->GetPhysicsLinearVelocity().X * 0.5), 60.0));
	MovementArrow->SetWorldRotation(FRotationMatrix::MakeFromX(StaticMeshComponent->GetPhysicsLinearVelocity().GetSafeNormal()).Rotator());
}

void APlayerCharacter::TurnLeftRight(float Value)
{
	AddControllerYawInput(Value);
}

void APlayerCharacter::TurnUpDown(float Value)
{
	AddControllerPitchInput(-Value);
}

