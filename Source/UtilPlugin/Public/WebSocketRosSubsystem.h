// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WebSocketsModule.h"
#include "IWebSocket.h"
#include "WebSocketRosSubsystem.generated.h"

class IWebSocket;

DECLARE_LOG_CATEGORY_EXTERN(LogMyWebSocket, Log, All);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWebSocketConnected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWebSocketConnectionError, const FString&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWebSocketClosed, int32, StatusCode, const FString&, Reason, bool, bWasClean);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWebSocketMessageReceived, const FString&, Message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWebSocketMessageSent, const FString&, Message);

UCLASS()
class UTILPLUGIN_API UWebSocketRosSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable)
	void InitRosConnect(FString ServerURI, FString ServerProtocol);
	UFUNCTION(BlueprintCallable)
	void SendMessage(const FString& Message);

	UFUNCTION(BlueprintPure)
	FString CurrentMessage() const;

	UPROPERTY(BlueprintAssignable)
	FOnWebSocketConnected OnWebSocketConnected;
	UPROPERTY(BlueprintAssignable)
	FOnWebSocketConnectionError OnWebSocketConnectionError;
	UPROPERTY(BlueprintAssignable)
	FOnWebSocketClosed OnWebSocketClosed;
	UPROPERTY(BlueprintAssignable)
	FOnWebSocketMessageReceived OnWebSocketMessageReceived;
	UPROPERTY(BlueprintAssignable)
	FOnWebSocketMessageSent OnWebSocketMessageSent;

private:
	void OnConnected() const;
	void OnConnectioinError(const FString& err) const;
	void OnClosed(const int statusCode, const FString& reason, const bool wasClean) const;
	void OnMessageReceived(const FString& msg);

	TSharedPtr<IWebSocket> Socket = nullptr;
	FString currentMsg;
};
