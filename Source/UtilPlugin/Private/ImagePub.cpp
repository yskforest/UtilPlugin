// Fill out your copyright notice in the Description page of Project Settings.

#include "ImagePub.h"

// Sets default values for this component's properties
UImagePub::UImagePub()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	// ...
}

// Called when the game starts
void UImagePub::BeginPlay()
{
	Super::BeginPlay();

	UROSIntegrationGameInstance* rosinst = Cast<UROSIntegrationGameInstance>(GetOwner()->GetGameInstance());
	if (!rosinst) {
		UE_LOG(LogTemp, Warning, TEXT("UROSIntegrationGameInstance is not set"));
		return;
	}
	ImagePublisher = NewObject<UTopic>(UTopic::StaticClass());
	ImagePublisher->Init(rosinst->ROSIntegrationCore, ImageTopicName, TEXT("sensor_msgs/Image"));
	ImagePublisher->Advertise();
}

void UImagePub::Publish(int width, int height, uint8* data)
{
	if (!ImagePublisher)
		return;

	FROSTime time = FROSTime::Now();

	TSharedPtr<ROSMessages::sensor_msgs::Image> imageMsg(new ROSMessages::sensor_msgs::Image());

	imageMsg->header.seq = 0;
	imageMsg->header.time = time;
	imageMsg->header.frame_id = ImageOpticalFrame;
	imageMsg->height = height;
	imageMsg->width = width;
	imageMsg->encoding = TEXT("bgra8");
	imageMsg->step = width * 4;
	imageMsg->data = data;
	ImagePublisher->Publish(imageMsg);
}
