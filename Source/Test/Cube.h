// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestGameModeBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "Cube.generated.h"

UENUM(BlueprintType)
enum ECubeType : uint8
{
	CLEAR,
	GREEN,
	RED,
};


UCLASS()
class TEST_API ACube2048 : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACube2048();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Cube")
	USceneComponent *SceneComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Cube")
	UStaticMeshComponent *StaticMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Cube")
	UBoxComponent *CollisionMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Cube")
	TArray<UMaterial*> CubeMaterials;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Cube")
	TEnumAsByte<ECubeType> CubeType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Sphere")
	USoundWave *PlayerSoundEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Sphere")
	USoundWave *CleanerSoundEffect;
	
	FTimerHandle MoveTimerHandle;
	FTimerDelegate TimerDelegate;
	ATestGameModeBase *GameMode; 
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	UFUNCTION(BlueprintImplementableEvent, category = "Cube")
	void SetTextureBasedOnCubeValue();
	void MoveInRandomDirection();
	UFUNCTION()
	void OverlappedEvent(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};

