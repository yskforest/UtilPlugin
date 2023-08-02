// Fill out your copyright notice in the Description page of Project Settings.

#include "FuncLib.h"

UTexture2D* UFuncLib::CreateTexture2D(int32 width, int32 height)
{
	UTexture2D* texture2d = UTexture2D::CreateTransient(width, height, EPixelFormat::PF_B8G8R8A8);
	return texture2d;
};
