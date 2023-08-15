// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <UObject/ObjectMacros.h>
#include <UObject/Object.h>

#include "ROSIntegration/Classes/RI/Topic.h"
#include "ROSIntegration/Classes/ROSIntegrationGameInstance.h"
#include "ROSIntegration/Public/geometry_msgs/PoseStamped.h"

#include "PoseSubsc.generated.h"

UCLASS()
class UTILPLUGIN_API APoseSubsc : public AActor
{
	GENERATED_BODY()

public:
	APoseSubsc();

	UFUNCTION(BlueprintImplementableEvent, Category = ROS)
	void OnPoseMessage(const FVector& location, const FQuat& quat);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ROS)
	FString SubscTopicName = TEXT("/pose");
	UPROPERTY(Transient, EditAnywhere, Category = ROS)
	UTopic* PoseSubscliber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ROS)
	FVector RecvLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ROS)
	FRotator RecvRotator;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void SetPose(const FVector& position, const FVector4& orientation);
};
