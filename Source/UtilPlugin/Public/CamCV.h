#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "Runtime/Engine/Classes/Engine/TextureRenderTarget2D.h"
#include "Components/SceneCaptureComponent2D.h"
#include "RHICommandList.h"
#include "ImagePub.h"
#include "TFPub.h"
#include "PosePub.h"

// important sort
#include "OpenCVHelper.h"
#include "PreOpenCVHeaders.h"
#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "PostOpenCVHeaders.h"

#include "CamCV.generated.h"

UCLASS()
class UTILPLUGIN_API ACamCV : public AActor
{
	GENERATED_BODY()

public:
	ACamCV();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneCaptureComponent2D* SC_Front;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterialInstanceDynamic* MaterialInstanceDynamic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* TextureCV = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSaveImage = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRosPublish = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D VideoSize = FVector2D(1920, 1080);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RefreshRate = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UImagePub* ImagePub;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTFPub* TFPub;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPosePub* PosePub;

protected:
	virtual void BeginPlay() override;

private:
	// privateにしないとEditor実行時にアウトライナから確認すると落ちるかも
	TArray<FColor> ColorDataFront;
	UTextureRenderTarget2D* RT_Front;
};
