// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ROSIntegration/Classes/RI/Topic.h"
#include "ROSIntegration/Classes/ROSIntegrationGameInstance.h"
#include "ROSIntegration/Public/geometry_msgs/PoseStamped.h"
#include "ROSIntegration/Public/std_msgs/String.h"

#include "RosSubsc.generated.h"

UENUM(BlueprintType, Category = "ROS")
enum class ESubscribeType : uint8
{
	String,
	StampedPose,
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UTILPLUGIN_API URosSubsc : public UActorComponent
{
	GENERATED_BODY()

public:
	URosSubsc();

	UFUNCTION(BlueprintImplementableEvent, Category = ROS)
	void OnPoseMessage(const FVector& location, const FQuat& quat);
	UFUNCTION(BlueprintImplementableEvent, Category = ROS)
	void OnStringMessage(const FString& string);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ROS)
	FString SubscTopicName = TEXT("/topic_name");
	UPROPERTY(Transient, EditAnywhere, Category = ROS)
	UTopic* Subscriber;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ROS)
	ESubscribeType SubscribeType = ESubscribeType::StampedPose;

protected:
	virtual void BeginPlay() override;

private:
	// Helper to keep track of self-destruction for async functions
	TSharedPtr<UTopic, ESPMode::ThreadSafe> _SelfPtr;
};
