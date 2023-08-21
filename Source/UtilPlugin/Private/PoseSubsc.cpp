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

	std::function<void(TSharedPtr<FROSBaseMsg>)> SubscribeCallback = [this](TSharedPtr<FROSBaseMsg> msg) -> void {
		auto ConcreteVectorMessage = StaticCastSharedPtr<ROSMessages::geometry_msgs::PoseStamped>(msg);
		if (ConcreteVectorMessage.IsValid()) {
			const auto p = ConcreteVectorMessage->pose.position;
			const auto q = ConcreteVectorMessage->pose.orientation;
			// UE_LOG(LogTemp, Log, TEXT("recv pose: %f, %f, %f"), p.x, p.y, p.z);
			// convert ROS -> UE coord
			const FVector position(p.x * 100, p.y * -100, p.z * 100);
			const FQuat orientation(-q.x, q.y, -q.z, q.w);

			AsyncTask(ENamedThreads::GameThread, [this, position, orientation]() {
				RecvLocation = position;
				RecvQuat = orientation;
				OnPoseMessage(position, orientation);
				// UE_LOG(LogTemp, Log, TEXT("async recv pose: %f, %f, %f"), position.X, position.Y, position.Z);
			});
		}
	};

	PoseSubscliber->Subscribe(SubscribeCallback);
}