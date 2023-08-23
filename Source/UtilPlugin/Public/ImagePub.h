// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ROSIntegration/Classes/RI/Topic.h"
#include "ROSIntegration/Classes/ROSIntegrationGameInstance.h"
#include "ROSIntegration/Public/std_msgs/String.h"
#include "ROSIntegration/Public/sensor_msgs/Image.h"

#include "ImagePub.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UTILPLUGIN_API UImagePub : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UImagePub();
	void Publish(int width, int height, uint8* data);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ROS")
	FString ImageOpticalFrame = TEXT("/unreal_ros/image_optical_frame");
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ROS")
	FString ImageTopicName = TEXT("/unreal_ros/image");
	UPROPERTY(Transient, EditAnywhere, Category = "ROS")
	UTopic* ImagePublisher;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
