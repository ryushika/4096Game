// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class TEST_API APlayerCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCharacter();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Sphere")
	USceneComponent *SceneComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Sphere")
	UStaticMeshComponent *StaticMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Sphere")
	USpringArmComponent *SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Sphere")
	UCameraComponent *Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Sphere")
	UArrowComponent *MovementArrow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Sphere")
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Cube")
	TArray<int> Values;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Sphere")
	int CubeValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Sphere")
	int MaterialValue;
public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveLeftRight(float Value);
	void TurnLeftRight(float Value);
	void TurnUpDown(float Value);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, category = "Cube")
	void SetMaterialBasedOnValue(int NewValue);

};
