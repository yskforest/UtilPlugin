// Fill out your copyright notice in the Description page of Project Settings.

#include "PoseSubsc.h"

// Sets default values for this component's properties
APoseSubsc::APoseSubsc()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

// Called when the game starts
void APoseSubsc::BeginPlay()
{
	Super::BeginPlay();

	UROSIntegrationGameInstance* rosinst = Cast<UROSIntegrationGameInstance>(GetGameInstance());
	if (!rosinst) {
		UE_LOG(LogTemp, Warning, TEXT("UROSIntegrationGameInstance is not set"));
		return;
	}
	PoseSubscliber = NewObject<UTopic>(UTopic::StaticClass());
	PoseSubscliber->Init(rosinst->ROSIntegrationCore, SubscTopicName, TEXT("geometry_msgs/PoseStamped"));

	// Create a std::function callback object
	std::function<void(TSharedPtr<FROSBaseMsg>)> SubscribeCallback = [](TSharedPtr<FROSBaseMsg> msg) -> void {
		auto Concrete = StaticCastSharedPtr<ROSMessages::geometry_msgs::PoseStamped>(msg);
		if (Concrete.IsValid()) {
			float x = Concrete->pose.position.x * 100;
			float y = Concrete->pose.position.y * -100;
			float z = Concrete->pose.position.z * 100;

			float rx = -Concrete->pose.orientation.x;
			float ry = Concrete->pose.orientation.y;
			float rz = -Concrete->pose.orientation.z;
			float rw = Concrete->pose.orientation.w;

			UE_LOG(LogTemp, Log, TEXT("recv pose: %f, %f, %f, %f, %f, %f, %f"), z, y, z, rx, ry, rz, rw);
		}
		return;
	};

	PoseSubscliber->Subscribe(SubscribeCallback);
}
