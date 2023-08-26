#include "RosSubsc.h"

URosSubsc::URosSubsc()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void URosSubsc::BeginPlay()
{
	Super::BeginPlay();

	UROSIntegrationGameInstance* rosinst = Cast<UROSIntegrationGameInstance>(GetOwner()->GetGameInstance());
	if (!rosinst) {
		UE_LOG(LogTemp, Warning, TEXT("UROSIntegrationGameInstance is not set"));
		return;
	}
	Subscriber = NewObject<UTopic>(UTopic::StaticClass());
	FString messageType = TEXT("");
	switch (SubscribeType) {
		case ESubscribeType::String:
			messageType = TEXT("std_msgs/String");
			break;
		case ESubscribeType::StampedPose:
			messageType = TEXT("geometry_msgs/PoseStamped");
			break;
		default:
			break;
	}
	Subscriber->Init(rosinst->ROSIntegrationCore, SubscTopicName, messageType);

	std::function<void(TSharedPtr<FROSBaseMsg>)> SubscribeCallback = nullptr;

	// AsyncTask内でのptr checkが必要かもしれない
	switch (SubscribeType) {
		case ESubscribeType::String:
			SubscribeCallback = [this](TSharedPtr<FROSBaseMsg> msg) -> void {
				auto MsgString = StaticCastSharedPtr<ROSMessages::std_msgs::String>(msg);
				if (MsgString.IsValid()) {
					const FString Data = MsgString->_Data;
					AsyncTask(ENamedThreads::GameThread, [this, Data]() {
						UE_LOG(LogTemp, Log, TEXT("async recv string: %s"), *Data);
						OnStringMessage(Data);
					});
				}
			};
			break;
		case ESubscribeType::StampedPose:
			SubscribeCallback = [this](TSharedPtr<FROSBaseMsg> msg) -> void {
				auto MsgStampedPose = StaticCastSharedPtr<ROSMessages::geometry_msgs::PoseStamped>(msg);
				if (MsgStampedPose.IsValid()) {
					const auto p = MsgStampedPose->pose.position;
					const auto q = MsgStampedPose->pose.orientation;
					UE_LOG(LogTemp, Log, TEXT("recv pose: %f, %f, %f"), p.x, p.y, p.z);
					// convert ROS -> UE coord
					const FVector position(p.x * 100, p.y * -100, p.z * 100);
					const FQuat orientation(-q.x, q.y, -q.z, q.w);

					AsyncTask(ENamedThreads::GameThread, [this, position, orientation]() {
						UE_LOG(LogTemp, Log, TEXT("async recv pose: %f, %f, %f"), position.X, position.Y, position.Z);
						OnPoseMessage(position, orientation);
					});
				}
			};
			break;
		default:
			break;
	}

	Subscriber->Subscribe(SubscribeCallback);
}
