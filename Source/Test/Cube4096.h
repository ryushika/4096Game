// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestGameModeBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "Cube4096.generated.h"

UENUM(BlueprintType)
enum ECubeValue : uint8
{
	TWO,
	FOUR,
	EIGHT,
	SIXTEEN,
	THIRTYTWO,
	SIXTYFOUR,
	HUNDREDTWENTYEIGHT,
	TWOHUNDREDFIFTYSIX,
	FIVEHUNDREDTWELVE,
	THOUSANDTWENTYFOUR,
	TWOTHOUSANDFOURTYEIGHT,
};

class ACube4096;


UCLASS()
class TEST_API ACube4096 : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACube4096();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Cube")
	USceneComponent *SceneComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Cube")
	UStaticMeshComponent *StaticMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Cube")
	UBoxComponent *CollisionMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Cube")
	TArray<UMaterial*> CubeMaterials;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Cube")
	TEnumAsByte<ECubeValue> CubeValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Cube")
	USoundWave *PlayerSoundEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Cube")
	USoundWave *CleanerSoundEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Cube")
	TArray<int> Values;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Cube")
	int Value; 
	
	FTimerHandle MoveTimerHandle;
	FTimerDelegate TimerDelegate;
	ATestGameModeBase *GameMode; 
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	UFUNCTION(BlueprintImplementableEvent, category = "Cube")
	void SetMaterialBasedOnValue(ECubeValue NewValue);
	
	void UpdateValue(int NewValue);
	void MoveInRandomDirection();
	UFUNCTION()
	void OverlappedEvent(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
