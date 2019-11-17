// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Engine/EngineTypes.h"

#include "UObject/UObjectGlobals.h"

#include "Engine/World.h"


// Sets default values
ASnakeCharacter::ASnakeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UStaticMeshComponent* MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("name"));

}

// Called when the game starts or when spawned
void ASnakeCharacter::BeginPlay()
{
	Super::BeginPlay();
	//ASnakeCharacter* SplineActor = GetWorld()->SpawnActor<ASnakeCharacter>(ASnakeCharacter::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
	//AActor* SplineActor = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, NULL, true);
	//ASnakeCharacter* ResultPawn = SpawnActor<ASnakeCharacter>(ASnakeCharacter::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, NULL, Instigator);
	//AActor* SplineActor = SpawnActor<AActor>(GetClass(), FVector::ZeroVector, FRotator::ZeroRotator, NULL, NULL, true);
	//AActor* SplineActor = GetWorld()->SpawnActorAbsolute()
	FActorSpawnParameters SpawnParams;
	//SpawnParams.SpawnCollisionHandlingOverride
	SplineActor = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	//SnakeSpline = CreateDefaultSubobject<USplineComponent>(TEXT("SnakeSpline")); //<UActorComponent>(USplineComponent::StaticClass(), this, TEXT("SnakeSpline"));
	//SnakeSpline = ConstructObject<USplineComponent>(SnakeSpline, SplineActor, "SnakeSpline"); //<UActorComponent>(USplineComponent::StaticClass(), this, TEXT("SnakeSpline"));
	//SplineActor->AddComponent("SplineComponent", false, SplineActor->GetActorTransform(), SnakeSpline);
	SnakeSpline = NewObject<USplineComponent>(SplineActor, "SnakeSpline");
	//Snake222 = NewObject<USplineComponent>(SplineActor, "Snake2222");
	//USplineComponent* Snake2222 = ConstructObject<USplineComponent>(SplineActor, "Snake2222");
	//SplineActor->AddComponent("USplineComponent", true, SplineActor->GetActorTransform(), SnakeSpline);
	

	//FDetachementTransformRules myDetachementRules;
	//SnakeSpline->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	//MeshComponent->SetStaticMesh(<your mesh as UStaticMesh*>);

	//TestMesh = ConstructObject<UStaticMesh>(StaticMeshCube, SplineActor, "SnakeSpline"); //<UActorComponent>(USplineComponent::StaticClass(), this, TEXT("SnakeSpline"));
	//SplineActor->AddInstanceComponent(USplineComponent::StaticClass());
	//SplineActor->AddComponent("SplineComponent", true, SplineActor->GetActorTransform(), USplineComponent::StaticClass());
	//SplineActor->AddComponent("SplineComponent2", false, SplineActor->GetActorTransform(), USplineComponent::StaticClass());
	//SplineActor->AddComponent("SplineComponent3", true, SplineActor->GetActorTransform(), NewObject<USplineComponent>(this, "SnakeSplinesss"));

	SplineActor->SetRootComponent(SnakeSpline);
	//SnakeSpline->AttachTo(SplineActor->GetRootComponent(), "none", EAttachLocation::KeepWorldPosition, false);
	
	//Snake222->SetupAttachment(SplineActor->GetRootComponent());
	//Snake222->AttachTo(SplineActor->GetRootComponent(), "none", EAttachLocation::KeepWorldPosition, false);
	//Snake222->AttachToComponent(SplineActor->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform); //AttachTo(SplineActor->GetRootComponent, NULL, );


	//SplineActor->GetComponents().Num;
	//UE_LOG(LogTemp, Warning, TEXT("ReplicatedLocation %d"), SplineActor->GetComponents().Num());

	//SplineActor->AddComponent(CreateDefaultSubobject<USplineComponent>(TEXT("SnakeSpline")));
	//

	//SplineActor->AddComponent(USplineComponent);
	//UE_LOG(LogTemp, Warning, TEXT("heyo spawning"));


}

// Called every frame
void ASnakeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Direction = GetMesh()->GetRightVector().GetSafeNormal();
	//UE_LOG(LogTemp, Warning, TEXT("ReplicatedLocation %s"), *Direction.ToString());
	
		//GetRelativeRotationFromWorld();
	
	//FVector Direction = GetMesh; //FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddActorWorldOffset(Direction*GetCharacterMovement()->GetMaxSpeed()*DeltaTime, true);
	//SplineActor->AddActorWorldOffset(Direction*GetCharacterMovement()->GetMaxSpeed()*DeltaTime, false);
	//SnakeSpline->SetWorldLocation(GetActorLocation());

	//UE_LOG(LogTemp, Warning, TEXT("ReplicatedLocation %s"), *SnakeSpline->GetComponentLocation().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("ReplicatedLocation %s"), *Snake222->GetComponentLocation().ToString());

	//AddMovementInput(Direction, 1);

	//FSplinePoint CurrentSplinePoint = FSplinePoint(0, GetActorLocation(), ESplinePointType::Constant, GetActorRotation(), FVector(1,1,1));
	//FSplinePoint CurrentSplinePoint;
	//CurrentSplinePoint.Position = GetActorLocation();
	//CurrentSplinePoint.Rotation = GetActorRotation();
	//SnakeSpline->AddPoint(CurrentSplinePoint, true);
	//SnakeSpline->SetWorldRotation
	SnakeSpline->AddSplinePoint(GetActorLocation(), ESplineCoordinateSpace::World, true);
	//SnakeSpline->SetWorldRotation(SnakeSpline->GetNumberOfSplinePoints() - 1, GetMesh()->SetRelativeRotation());
	FInterpCurveQuat& SplineRotInfo = SnakeSpline->GetSplinePointsRotation();
	FInterpCurvePoint<FQuat>& EditedRotPoint = SplineRotInfo.Points[SnakeSpline->GetNumberOfSplinePoints() - 1];
	EditedRotPoint.OutVal = GetActorRotation().Quaternion();

	//UE_LOG(LogTemp, Warning, TEXT("ReplicatedLocation %f"), SnakeSpline->GetSplineLength());

	for (int n = 0; n < Followers.Num(); n++)
	{
		FHitResult Hit;
		FVector newLocation = FVector(SnakeSpline->GetLocationAtDistanceAlongSpline(SnakeSpline->GetSplineLength() - ((n+1)*followersDistance), ESplineCoordinateSpace::World));
		Followers[n]->SetActorLocation(newLocation, true, &Hit, ETeleportType::TeleportPhysics);
		Followers[n]->SetActorRotation(SnakeSpline->GetRotationAtDistanceAlongSpline(SnakeSpline->GetSplineLength() - ((n+1)*followersDistance), ESplineCoordinateSpace::World), ETeleportType::TeleportPhysics);
	}

}

// Called to bind functionality to input
void ASnakeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ASnakeCharacter::following(AActor* NewFollower)
{
	Followers.Add(NewFollower);
	UE_LOG(LogTemp, Warning, TEXT("NewFollower: %d"), Followers.Num());
	//UE_LOG(LogTemp, Warning, TEXT("NewFollower: %s"), *NewFollower->GetName());
}

