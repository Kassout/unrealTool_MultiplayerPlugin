// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Menu.generated.h"

UCLASS()
class MULTIPLAYERSESSIONS_API UMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup(int32 NumberOfPublicConnections = 4, FString TypeOfMatch = FString(TEXT("FreeForAll")), FString LobbyPath = FString(TEXT("/Game/ThirdPerson/Maps/Lobby")));
	
protected:
	virtual bool Initialize() override;

	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

	//
	// Callbacks for the custom delegates on the MultiplayerSessionsSubsystem.
	//
	/**
	 * Called on broadcasted create session event.
	 * @param bWasSuccessful	Did the online game session creation was successful.
	 */
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);

	/**
	 * Called on broadcasted find sessions event.
	 * @param SessionResults	The different session properties found with the given criteria.
	 * @param bWasSuccessful	Did the online game session finding was successful.
	 */
	void OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);

	/**
	 * Called on broadcasted join session event.
	 * @param Result	Result type of the join session event.
	 */
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);

	/**
	 * Called on broadcasted destroy session event.
	 * @param bWasSuccessful	Did the online game session destruction was successful.
	 */
	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);

	/**
	 * Called on broadcasted start session event.
	 * @param bWasSuccessful	Did the online game session starting was successful.
	 */
	UFUNCTION()
	void OnStartSession(bool bWasSuccessful);

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

	UFUNCTION()
	void HostButtonClicked();

	UFUNCTION()
	void JoinButtonClicked();

	void MenuTearDown();
	
	// The subsystem designed to handle all online session functionality.
	class UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;

	// Integer value representing the session number of public connections allowed.
	int32 NumPublicConnections{ 4 };
	
	// String message representing the session match type.
	FString MatchType{TEXT("FreeForAll")};

	// String message representing the path to the Lobby map for player travel once hosting or joining a session is complete and successful.
	FString PathToLobby{TEXT("")};
};
