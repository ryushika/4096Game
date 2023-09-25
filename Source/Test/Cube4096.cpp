// Fill out your copyright notice in the Description page of Project Settings.


#include "Cube4096.h"

#include "PlayerCharacter.h"

// Sets default values
ACube4096::ACube4096()
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
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &ACube4096::OverlappedEvent);

}

// Called when the game starts or when spawned
void ACube4096::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle,this, &ACube4096::MoveInRandomDirection, FMath::RandRange(1.0, 3.0),true);
	GameMode = (ATestGameModeBase*)GetWorld()->GetAuthGameMode();
	Values = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};
	CubeValue = (ECubeValue)(FMath::RandRange(GameMode->MinValue, GameMode->MaxValue));
	UpdateValue(Values[CubeValue]);
	SetMaterialBasedOnValue(CubeValue);
}

void ACube4096::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(MoveTimerHandle);
}


void ACube4096::MoveInRandomDirection()
{
	FVector Impulse = FVector(FMath::FRandRange(-740.0, 740.0), FMath::FRandRange(-580.0, 740.0), 0);
	StaticMeshComponent->AddImpulse(Impulse * FMath::RandRange(50, 100));
}

void ACube4096::OverlappedEvent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ACube4096>(OtherActor) != nullptr) 
	{
		if (CubeValue == Cast<ACube4096>(OtherActor)->CubeValue)
		{
			UpdateValue(Value*2);
			SetMaterialBasedOnValue(CubeValue);
			OtherActor->Destroy();
			GameMode->Score += Value;
			GameMode->UpdateHUD();

		}
		if (PlayerSoundEffect != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, PlayerSoundEffect, GetActorLocation());
		}
	}
	if (OtherActor->ActorHasTag("Player"))
	{
		if (Value < Cast<APlayerCharacter>(OtherActor)->CubeValue)
		{
			UpdateValue(Cast<APlayerCharacter>(OtherActor)->CubeValue);
			SetMaterialBasedOnValue(CubeValue);
		}
	}
}

void ACube4096::UpdateValue(int NewValue)
{
	switch (NewValue)
	{
	case 2:
		{
			Value = 2;
			CubeValue = TWO;
		}break;
	case 4:
		{
			Value = 4;
			CubeValue = FOUR;
			StaticMeshComponent->SetRelativeScale3D(FVector(0.3, 0.3, 0.3));
		}break;
	case 8:
		{
			Value = 8;
			CubeValue = EIGHT;
			StaticMeshComponent->SetRelativeScale3D(FVector(0.4, 0.4, 0.4));
		}break;
	case 16:
		{
			Value = 16;
			CubeValue = SIXTEEN;
			StaticMeshComponent->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));
		}break;
	case 32:
		{
			Value = 32;
			CubeValue = THIRTYTWO;
		}break;
	case 64:
		{
			Value = 64;
			CubeValue = SIXTYFOUR;
		}break;
	case 128:
		{
			Value = 128;
			CubeValue = HUNDREDTWENTYEIGHT;
			StaticMeshComponent->SetRelativeScale3D(FVector(0.6, 0.6, 0.6));
		}break;
	case 256:
		{
			Value = 256;
			CubeValue = TWOHUNDREDFIFTYSIX;
			StaticMeshComponent->SetRelativeScale3D(FVector(0.65, 0.65, 0.65));
		}break;
	case 512:
		{
			Value = 512;
			CubeValue = FIVEHUNDREDTWELVE;
			StaticMeshComponent->SetRelativeScale3D(FVector(0.7, 0.7, 0.7));
		}break;
	case 1024:
		{
			Value = 1024;
			CubeValue = THOUSANDTWENTYFOUR;
			StaticMeshComponent->SetRelativeScale3D(FVector(0.75, 0.75, 0.75));
		}break;
	case 2048:
		{
			Value = 2048;
			CubeValue = TWOTHOUSANDFOURTYEIGHT;
			StaticMeshComponent->SetRelativeScale3D(FVector(1, 1, 1));
		}break;
	}	
}
