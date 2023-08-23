// Fill out your copyright notice in the Description page of Project Settings.

#include "StampedPosePub.h"

UStampedPosePub::UStampedPosePub()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStampedPosePub::BeginPlay()
{
	Super::BeginPlay();

	if (!bEnablePublish || !bEnableTick) {
		PrimaryComponentTick.bCanEverTick = false;
		PrimaryComponentTick.bStartWithTickEnabled = false;
		return;
	}

	UROSIntegrationGameInstance* rosinst = Cast<UROSIntegrationGameInstance>(GetOwner()->GetGameInstance());
	if (!rosinst) {
		UE_LOG(LogTemp, Warning, TEXT("UROSIntegrationGameInstance is not set"));
		return;
	}

	Publisher = NewObject<UTopic>(UTopic::StaticClass());
	Publisher->Init(rosinst->ROSIntegrationCore, TopicName, TEXT("geometry_msgs/PoseStamped"));
	Publisher->Advertise();
}

void UStampedPosePub::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	static float RefreshTimer = 0.0f;
	static int FrameCount = 0;

	float SecPerFrame = 1.0f / RefreshRate;
	RefreshTimer += DeltaTime;
	if (SecPerFrame <= RefreshTimer) {
		RefreshTimer -= SecPerFrame;
		Publish();
	}
}

void UStampedPosePub::Publish()
{
	if (!Publisher || !bEnablePublish) {
		return;
	}

	FROSTime time = FROSTime::Now();
	FVector location = GetComponentLocation();
	FQuat quat = GetComponentQuat();

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
	Publisher->Publish(poseMsg);
}
