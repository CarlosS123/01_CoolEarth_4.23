// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SplineComponent.h"
#include "SnakeCharacter.generated.h"

UCLASS()
class COOLEARTH_API ASnakeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASnakeCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
		USplineComponent* SnakeSpline;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		//USplineComponent* Snake222;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
		AActor* SplineActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
		float followersDistance = 200;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
		bool isGameOver = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
		TArray<AActor*> Followers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* TestMesh;

	UFUNCTION(BlueprintCallable, Category = "Snake")
		void following(AActor* NewFollower);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
