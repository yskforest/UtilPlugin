// Fill out your copyright notice in the Description page of Project Settings.

#include "WebSocketRosSubsystem.h"

DEFINE_LOG_CATEGORY(LogMyWebSocket);

void UWebSocketRosSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(LogMyWebSocket, Log, TEXT("WebSocketRosSubsystem: Initialized!"));
}

void UWebSocketRosSubsystem::Deinitialize()
{
	if (Socket) {
		Socket->Close();
		Socket = nullptr;
	}
}

void UWebSocketRosSubsystem::InitRosConnect(FString ServerURI, FString ServerProtocol)
{
	if (Socket) {
		UE_LOG(LogMyWebSocket, Log, TEXT("WebSocketRosSubsystem: socket already exists!"));
	}

	Socket = FWebSocketsModule::Get().CreateWebSocket(ServerURI, ServerProtocol);

	Socket->OnConnected().AddUObject(this, &UWebSocketRosSubsystem::OnConnected);
	Socket->OnConnectionError().AddUObject(this, &UWebSocketRosSubsystem::OnConnectioinError);
	Socket->OnClosed().AddUObject(this, &UWebSocketRosSubsystem::OnClosed);
	Socket->OnMessage().AddUObject(this, &UWebSocketRosSubsystem::OnMessageReceived);

	Socket->Connect();
	UE_LOG(LogMyWebSocket, Log, TEXT("WebSocketRosSubsystem: create socket!"));
}

FString UWebSocketRosSubsystem::CurrentMessage() const
{
	return currentMsg;
}

void UWebSocketRosSubsystem::SendMessage(const FString& Message)
{
	Socket->Send(Message);
}

void UWebSocketRosSubsystem::OnConnected() const
{
	OnWebSocketConnected.Broadcast();
	UE_LOG(LogMyWebSocket, Log, TEXT("OnWebSocketConnected"));
}

void UWebSocketRosSubsystem::OnConnectioinError(const FString& err) const
{
	OnWebSocketConnectionError.Broadcast(err);
	UE_LOG(LogMyWebSocket, Warning, TEXT("OnWebSocketConnectionError: %s"), *err);
}

void UWebSocketRosSubsystem::OnClosed(const int statusCode, const FString& reason, const bool wasClean) const
{
	OnWebSocketClosed.Broadcast(statusCode, reason, wasClean);
	UE_LOG(LogMyWebSocket, Log, TEXT("OnSocketClosed: statuscode %d, reason %s, wasClean %s"), statusCode, *reason, (wasClean ? TEXT("true") : TEXT("false")));
}

void UWebSocketRosSubsystem::OnMessageReceived(const FString& msg)
{
	UE_LOG(LogMyWebSocket, Log, TEXT("OnSocketMessageReceived: %s"), *msg);
	currentMsg = msg;
	OnWebSocketMessageReceived.Broadcast(currentMsg);
}
