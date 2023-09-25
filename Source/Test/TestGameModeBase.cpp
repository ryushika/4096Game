// Copyright Epic Games, Inc. All Rights Reserved.


#include "TestGameModeBase.h"
#include "UnrealWidgetFwd.h"

void ATestGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	MinValue = 0;
	MaxValue = 1; 
	if (IsValid(WidgetClass))
	{
		GameHUD = Cast<UGameHUD>(CreateWidget(GetWorld(), WidgetClass));

		if (GameHUD != nullptr)
		{
			GameHUD->AddToViewport();
		}
	}
	GetWorld()->GetTimerManager().SetTimer(StageTimerHandle,this, &ATestGameModeBase::NextStage, 20,true);
	
}

void ATestGameModeBase::UpdateHUD()
{
	GameHUD->Update(CleanerCount, Score);	 
}


void ATestGameModeBase::UpdateCubeCount(int Count)
{
	MarkedTotal += Count;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Total %d/13"), MarkedTotal));
	if (MarkedTotal >= 13 && CleanerCount == 0)
	{
		if (!Won)
		{
			Victory();
			Won = true;
		}
		 
	}
}

void ATestGameModeBase::SecondLevel()
{
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle,this, &ATestGameModeBase::SpawnCubes, 3,true);
}

void ATestGameModeBase::SpawnCubes()
{
	FTransform NewTransform = FTransform(FRotator{}, FVector(FMath::FRandRange(-740.0, 740.0),
		FMath::FRandRange(-580.0, 740.0), 150),FVector{ 1, 1, 1 });
	if (CubeToSpawn != nullptr)
	{
		AActor *NewCube = GetWorld()->SpawnActor<AActor>(CubeToSpawn, NewTransform);
	}
		
}
