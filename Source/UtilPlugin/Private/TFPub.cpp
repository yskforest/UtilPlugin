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
	TFPublisher->Init(rosinst->ROSIntegrationCore, TFTopicName, TEXT("geometry_msgs/Transfrom"));
}

void UTFPub::Publish()
{
	// FVector Location = GetComponentLocation();
	// FQuat Rotation = GetComponentQuat();
	// FVe

	// FVector Location = OwnerActor->GetActorLoction();
	// FQuat Rotation = OwnerActor->GetActorQuat();

	// // Convert to meters and ROS coordinate system
	// double x = Location.X / 100.0f;
	// double y = -Location.Y / 100.0f;
	// double z = Location.Z / 100.0f;
	// double rx = -Rotation.X;
	// double ry = Rotation.Y;
	// double rz = -Rotation.Z;
	// double rw = Rotation.W;

	// TSharedPtr<ROSMessages::geometry_mags::Transform> TFMsg(new ROSMessages::geometry_mags::Transform());
	// TFMsg->translation.x = x;
	// TFMsg->translation.y = y;
	// TFMsg->translation.z = z;
	// TFMsg->rotation.x = rx;
	// TFMsg->rotation.y = ry;
	// TFMsg->rotation.z = rz;
	// TFMsg->rotation.w = rw;

	// TFPublisher->Publish(TFMsg);
}
