// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ROS")
	FString SubscTopicName = TEXT("/pose");
	UPROPERTY(Transient, EditAnywhere, Category = "ROS")
	UTopic* PoseSubscliber;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
