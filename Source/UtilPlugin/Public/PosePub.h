// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ROSIntegration/Classes/RI/Topic.h"
#include "ROSIntegration/Classes/ROSIntegrationGameInstance.h"
#include "ROSIntegration/Public/geometry_msgs/PoseStamped.h"

#include "PosePub.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UTILPLUGIN_API UPosePub : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPosePub();
	void Publish();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ROS")
	FString PoseTopicName = TEXT("/unreal_ros/pose");
	UPROPERTY(Transient, EditAnywhere, Category = "ROS")
	UTopic* PosePublisher;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	AActor* OwnerActor;
};
