// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "StampedPosePub.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UTILPLUGIN_API UStampedPosePub : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStampedPosePub();

	UFUNCTION(BlueprintCallable)
	void Publish();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnablePublish = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableTick = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RefreshRate = 30.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TopicName = TEXT("/unreal_ros/pose");
	UPROPERTY(Transient, EditAnywhere)
	UTopic* Publisher;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
