// Fill out your copyright notice in the Description page of Project Settings.

#include "CamCV.h"
#include "OpenCVHelper.h"

#include "PreOpenCVHeaders.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "PostOpenCVHeaders.h"

// Sets default values
ACamCV::ACamCV()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACamCV::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACamCV::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
