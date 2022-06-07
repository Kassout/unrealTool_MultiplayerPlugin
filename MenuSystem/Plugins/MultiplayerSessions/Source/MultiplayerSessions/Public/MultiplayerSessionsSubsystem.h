// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "MultiplayerSessionsSubsystem.generated.h"

//
// Declaring our own custom delegates for the Menu class to bind callbacks to.
// MULTICAST: Once it's broadcast, multiple classes can bind their functions to it.
// DYNAMIC: The delegate can be serialized and they can be saved or loaded from within a blueprint graph (event dispatchers in blueprints).
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnCreateSessionComplete, bool, bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiplayerOnFindSessionsComplete, const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_OneParam(FMultiplayerOnJoinSessionComplete, EOnJoinSessionCompleteResult::Type Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnDestroySessionComplete, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnStartSessionComplete, bool, bWasSuccessful);

UCLASS()
class MULTIPLAYERSESSIONS_API UMultiplayerSessionsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	////////////////////////////////////////////////////////////////////
	// Our own custom delegates for the Menu class to bind callbacks to.
	//
	// Function callback delegate on create session complete event trigger.
	FMultiplayerOnCreateSessionComplete MultiplayerOnCreateSessionComplete;
	
	// Function callback delegate on find sessions complete event trigger.
	FMultiplayerOnFindSessionsComplete MultiplayerOnFindSessionsComplete;
	
	// Function callback delegate on join session complete event trigger.
	FMultiplayerOnJoinSessionComplete MultiplayerOnJoinSessionComplete;
	
	// Function callback delegate on destroy session complete event trigger.
	FMultiplayerOnDestroySessionComplete MultiplayerOnDestroySessionComplete;
	
	// Function callback delegate on start session complete event trigger.
	FMultiplayerOnStartSessionComplete MultiplayerOnStartSessionComplete;

	/** Default constructor */
	UMultiplayerSessionsSubsystem();

	////////////////////////////////////////////////////////////////////
	// To handle session functionality. The Menu class will call these.
	//
	/**
	 * Called to create an online game session.
	 * @param NumPublicConnections	Number of public connections to allowed for the session.
	 * @param MatchType		The match type to initialized for the session.
	 */
	void CreateSession(int32 NumPublicConnections, FString MatchType);

	/**
	 * Called to find online game sessions.
	 * @param MaxSearchResults	Number of sessions found.
	 */
	void FindSessions(int32 MaxSearchResults);

	/**
	 * Called to join an online game session.
	 * @param SessionResult		The properties of the joined session.
	 */
	void JoinSession(const FOnlineSessionSearchResult& SessionResult);

	/** Called to destroy an online game session. */
	void DestroySession();

	/** Called to start an online game session. */
	void StartSession();

protected:
	////////////////////////////////////////////////////////////////////////////////////////////////
	// Internal callbacks for the delegates we'll add to the Online Session Interface delegate list.
	// These don't need to be called outside this class.
	//
	/**
	 * Called on create session complete event.
	 * @param SessionName	Name of the online game session.
	 * @param bWasSuccessful	Did the online game session creation was successful.
	 */
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	/**
	 * Called on find sessions complete event.
	 * @param bWasSuccessful	Did the online game session creation was successful.
	 */
	void OnFindSessionsComplete(bool bWasSuccessful);

	/**
	 * Called on join session complete event.
	 * @param SessionName	Name of the online game session.
	 * @param Result	Result type of the join session event.
	 */
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	/**
	 * Called on destroy session complete event.
	 * @param SessionName	Name of the online game session.
	 * @param bWasSuccessful	Did the online game session creation was successful.
	 */
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

	/**
	 * Called on start session complete event.
	 * @param SessionName	Name of the online game session.
	 * @param bWasSuccessful	Did the online game session creation was successful.
	 */
	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);

private:
	// Smart pointer to the online session interface object.
	IOnlineSessionPtr SessionInterface;
	
	// Smart pointer to the last online session creation settings.
	TSharedPtr<FOnlineSessionSettings> LastSessionSettings;
	
	// Smart pointer to the last online session search settings
	TSharedPtr<FOnlineSessionSearch> LastSessionSearch;
	
	// Boolean value representing the create session on destroy status of the multiplayer sessions subsystem.
	bool bCreateSessionOnDestroy{ false };
	
	// Integer value representing the last session number of public connections allowed.
	int32 LastNumPublicConnections;
	
	// String message representing the last session match type.
	FString LastMatchType;

	///////////////////////////////////////////////////////////////////////////
	// To add to the Online Session Interface delegate list.
	// We'll bind our MultiplayerSessionsSubsystem internal callbacks on these.
	//
	/** Event fired on create session complete event. */
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;

	/** Lifecycle manager of the create session complete delegate. */
	FDelegateHandle CreateSessionCompleteDelegateHandle;

	/** Event fired on find sessions complete event. */
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;

	/** Lifecycle manager of the find sessions complete delegate. */
	FDelegateHandle FindSessionsCompleteDelegateHandle;

	/** Event fired on join session complete event. */
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;

	/** Lifecycle manager of the join session complete delegate. */
	FDelegateHandle JoinSessionCompleteDelegateHandle;

	/** Event fired on destroy session complete event. */
	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;

	/** Lifecycle manager of the destroy session complete delegate. */
	FDelegateHandle DestroySessionCompleteDelegateHandle;

	/** Event fired on start session complete event. */
	FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;

	/** Lifecycle manager of the start session complete delegate. */
	FDelegateHandle StartSessionCompleteDelegateHandle;
};
