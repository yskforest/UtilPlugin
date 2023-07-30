// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"

#include "ROSIntegration/Classes/RI/Topic.h"
#include "ROSIntegration/Classes/ROSIntegrationGameInstance.h"
#include "ROSIntegration/Public/std_msgs/String.h"
#include "ROSIntegration/Public/geometry_msgs/Transform.h"
#include "ROSIntegration/Public/geometry_msgs/Vector3.h"

#include "TFPub.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UTILPLUGIN_API UTFPub : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTFPub();
	// UFUNCTION(Category = "ROS");
	// OwnerのActorのTransformをPublishする
	void Publish();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ROS")
	FString TFTopicName = TEXT("/unreal_ros/tf");
	UPROPERTY(Transient, EditAnywhere, Category = "ROS")
	UTopic* TFPublisher;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ROS")
	FString LocTopicName = TEXT("/unreal_ros/location");
	UPROPERTY(Transient, EditAnywhere, Category = "ROS")
	UTopic* LocPublisher;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ROS")
	FString RotTopicName = TEXT("/unreal_ros/rotation");
	UPROPERTY(Transient, EditAnywhere, Category = "ROS")
	UTopic* RotPublisher;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	AActor* OwnerActor = nullptr;
};
