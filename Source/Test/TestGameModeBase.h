// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameHUD.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "TestGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API ATestGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	int CleanerCount;

	UPROPERTY(BlueprintReadWrite)
	int MarkedTotal;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WidgetClass;
	
	UPROPERTY(VisibleInstanceOnly)
	UGameHUD* GameHUD;
	bool Won = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Cube")
	int MinValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Cube")
	int MaxValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Cube")
    int Score;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Cube")
	TSubclassOf<AActor> CubeToSpawn;
	
	FTimerHandle StageTimerHandle;
	FTimerHandle SpawnTimerHandle;
	FTimerDelegate TimerDelegate;

	UFUNCTION()
	void UpdateHUD();
	UFUNCTION(BlueprintImplementableEvent)
	void Victory();
	UFUNCTION()
	void UpdateCubeCount(int Count);
	UFUNCTION(BlueprintImplementableEvent)
	void NextStage();
	UFUNCTION(BlueprintCallable)
	void SecondLevel();
	UFUNCTION()
	void SpawnCubes();

	virtual void BeginPlay() override;
};
