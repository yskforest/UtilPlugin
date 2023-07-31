// Fill out your copyright notice in the Description page of Project Settings.

#include "TFPub.h"

// Sets default values for this component's properties
UTFPub::UTFPub()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

// Called when the game starts
void UTFPub::BeginPlay()
{
	Super::BeginPlay();

	OwnerActor = GetOwner();

	UROSIntegrationGameInstance* rosinst = Cast<UROSIntegrationGameInstance>(GetOwner()->GetGameInstance());
	if (!rosinst) {
		UE_LOG(LogTemp, Warning, TEXT("UROSIntegrationGameInstance is not set"));
		return;
	}

	// TFPublisher = NewObject<UTopic>(UTopic::StaticClass());
	// TFPublisher->Init(rosinst->ROSIntegrationCore, TFTopicName, TEXT("geometry_msgs/Transform"));
	// TFPublisher->Advertise();
	LocPublisher = NewObject<UTopic>(UTopic::StaticClass());
	LocPublisher->Init(rosinst->ROSIntegrationCore, LocTopicName, TEXT("geometry_msgs/Vector3"));
	LocPublisher->Advertise();
	RotPublisher = NewObject<UTopic>(UTopic::StaticClass());
	RotPublisher->Init(rosinst->ROSIntegrationCore, RotTopicName, TEXT("geometry_msgs/Vector3"));
	RotPublisher->Advertise();
}

void UTFPub::Publish()
{
	if (!LocPublisher)
		return;

	FVector location = OwnerActor->GetActorLocation();
	// Convert to meters and ROS coordinate system
	double x = location.X / 100.0f;
	double y = -location.Y / 100.0f;
	double z = location.Z / 100.0f;
	// FQuat quat = OwnerActor->GetActorQuat();
	// double rx = -quat.X;
	// double ry = quat.Y;
	// double rz = -quat.Z;
	// double rw = quat.W;

	TSharedPtr<ROSMessages::geometry_msgs::Vector3> locMsg(new ROSMessages::geometry_msgs::Vector3());
	locMsg->x = x;
	locMsg->y = y;
	locMsg->z = z;
	LocPublisher->Publish(locMsg);

	FRotator rotation =OwnerActor->GetActorRotation();
	// 座標系変換無考慮
	TSharedPtr<ROSMessages::geometry_msgs::Vector3> rotMsg(new ROSMessages::geometry_msgs::Vector3());
	rotMsg->x = rotation.Roll;
	rotMsg->y = rotation.Pitch;
	rotMsg->z = rotation.Yaw;
	RotPublisher->Publish(rotMsg);

	// Transformなぜか送信できない
	// TSharedPtr<ROSMessages::geometry_msgs::Transform> TFMsg(new ROSMessages::geometry_msgs::Transform());
	// TFMsg->translation.x = x;
	// TFMsg->translation.y = y;
	// TFMsg->translation.z = z;
	// TFMsg->rotation.x = rx;
	// TFMsg->rotation.y = ry;
	// TFMsg->rotation.z = rz;
	// TFMsg->rotation.w = rw;
	// // UE_LOG(LogTemp, Log, TEXT("tf: %f,%f,%f"), x, y, z);
	// TFPublisher->Publish(TFMsg);
}
