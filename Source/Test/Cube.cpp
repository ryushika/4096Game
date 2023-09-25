// Fill out your copyright notice in the Description page of Project Settings.

#include "Cube.h"

// Sets default values
ACube2048::ACube2048()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Box"));
	
	RootComponent = SceneComponent;
	StaticMeshComponent->SetupAttachment(SceneComponent);
	CollisionMesh->SetupAttachment(StaticMeshComponent);
	StaticMeshComponent->SetSimulatePhysics(true);
	CollisionMesh->SetCollisionProfileName(TEXT("Overlap All"));
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &ACube2048::OverlappedEvent);

}

// Called when the game starts or when spawned
void ACube2048::BeginPlay()
{
	Super::BeginPlay();
	SetTextureBasedOnCubeValue();
	GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle,this, &ACube2048::MoveInRandomDirection, FMath::RandRange(1.0, 3.0),true);
	GameMode = (ATestGameModeBase*)GetWorld()->GetAuthGameMode();

	CubeType = (ECubeType)(FMath::RandRange(0, 2));
	switch (CubeType)
	{
	case RED:
		{
			Tags.Add("Marked");
			GameMode->UpdateCubeCount(1);
		}break;
	case GREEN:
		{
			Tags.Add("Cleaner");
			GameMode->CleanerCount += 1;
			GameMode->UpdateHUD();
		}break;
	case CLEAR:
		{
			Tags.Add("Clear");
		}break;
	}	
}

void ACube2048::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(MoveTimerHandle);
}

void ACube2048::MoveInRandomDirection()
{
	FVector Impulse = FVector(FMath::FRandRange(-740.0, 740.0), FMath::FRandRange(-580.0, 740.0), 0);
	StaticMeshComponent->AddImpulse(Impulse * FMath::RandRange(50, 100));
}

void ACube2048::OverlappedEvent(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(TEXT("Player")))
	{
		if (ActorHasTag(TEXT("Cleaner")))
		{
			Tags.Remove("Cleaner");
			GameMode->CleanerCount -= 1;
			GameMode->UpdateCubeCount(1);
			GameMode->UpdateHUD();
		}
		else if (ActorHasTag(TEXT("Clear")))
		{
			GameMode->UpdateCubeCount(1);
		}
		if (PlayerSoundEffect != nullptr && CubeType != RED)
		{
			UGameplayStatics::PlaySoundAtLocation(this, PlayerSoundEffect, GetActorLocation());
		}
		CubeType = RED;
		Tags.Remove("Cleaner");
		Tags.Remove("Clear");
		Tags.Add("Marked");
	}
	else if (OtherActor->ActorHasTag(TEXT("Marked")))
	{
		if (CubeType == CLEAR)
			{
				GameMode->UpdateCubeCount(1);
				CubeType = RED;
				Tags.Remove("Clear");
				Tags.Add("Marked");
			}
	}
	else if (OtherActor->ActorHasTag(TEXT("Cleaner")))
	{
		if (CubeType != GREEN)
		{
			if (CubeType != CLEAR)
			{
				GameMode->UpdateCubeCount(-1);
			}
			CubeType = CLEAR;
			Tags.Remove("Marked");
			Tags.Add("Clear");
			
			if (CleanerSoundEffect != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, CleanerSoundEffect, GetActorLocation());
			}
		}
	}
	SetTextureBasedOnCubeValue();
}