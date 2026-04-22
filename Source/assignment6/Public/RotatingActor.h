// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingActor.generated.h"

UCLASS()
class ASSIGNMENT6_API ARotatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotatingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//Root Scene Component
	UPROPERTY(EditAnywhere)
	USceneComponent* SceneComponent;
	
	//Static Mesh Component
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	bool isDisappear = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float DisappearTime = 3.0f;
	
	//Rotating Factor
	UPROPERTY(EditAnywhere)
	float RotationSpeed;
	
	FTimerHandle DisappearTimerHandle;
	void HandleDisappear();

};
