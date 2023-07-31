// Fill out your copyright notice in the Description page of Project Settings.

#include "PosePub.h"

// Sets default values for this component's properties
UPosePub::UPosePub()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

// Called when the game starts
void UPosePub::BeginPlay()
{
	Super::BeginPlay();

	OwnerActor = GetOwner();

	UROSIntegrationGameInstance* rosinst = Cast<UROSIntegrationGameInstance>(GetOwner()->GetGameInstance());
	if (!rosinst) {
		UE_LOG(LogTemp, Warning, TEXT("UROSIntegrationGameInstance is not set"));
		return;
	}

	PosePublisher = NewObject<UTopic>(UTopic::StaticClass());
	PosePublisher->Init(rosinst->ROSIntegrationCore, PoseTopicName, TEXT("geometry_msgs/PoseStamped"));
	PosePublisher->Advertise();
}

void UPosePub::Publish()
{
	if (!PosePublisher)
		return;

	FROSTime time = FROSTime::Now();
	FVector location = GetOwner()->GetActorLocation();
	FQuat quat = GetOwner()->GetActorQuat();

	TSharedPtr<ROSMessages::geometry_msgs::PoseStamped> poseMsg(new ROSMessages::geometry_msgs::PoseStamped());

	poseMsg->header.seq = 0;
	poseMsg->header.time = time;
	poseMsg->header.frame_id = TEXT("map");
	// Convert to meters and ROS coordinate system
	poseMsg->pose.position.x = location.X / 100.0f;
	poseMsg->pose.position.y = -location.Y / 100.0f;
	poseMsg->pose.position.z = location.Z / 100.0f;
	poseMsg->pose.orientation.x = -quat.X;
	poseMsg->pose.orientation.y = quat.Y;
	poseMsg->pose.orientation.z = -quat.Z;
	poseMsg->pose.orientation.w = quat.W;
	PosePublisher->Publish(poseMsg);
}
