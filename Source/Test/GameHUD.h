// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHUD.generated.h"

UCLASS()
class TEST_API UGameHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, category = "HUD")
	class UImage* Icon;
	UPROPERTY(BlueprintReadWrite, category = "HUD")
	class UTextBlock* TextLabel;

	UPROPERTY(BlueprintReadWrite, category = "HUD")
	class UTextBlock* Score;

public:
	UFUNCTION()
	void Update(int CleanerCount, int NewScore);
	
	virtual void NativeConstruct() override;
};
