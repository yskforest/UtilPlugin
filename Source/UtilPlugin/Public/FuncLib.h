// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"

#include "FuncLib.generated.h"

/**
 *
 */
UCLASS()
class UTILPLUGIN_API UFuncLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static UTexture2D* CreateTexture2D(int32 width, int32 height);
};
