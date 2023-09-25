// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "Components/Textblock.h"


void UGameHUD::NativeConstruct()
{
	Super::NativeConstruct();
	TextLabel->SetText(FText::AsNumber(1));
}

void UGameHUD::Update(int CleanerCount, int NewScore)
{
	TextLabel->SetText(FText::AsNumber(CleanerCount));
	Score->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), NewScore)));
}
