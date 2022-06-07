// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "MenuSystemCharacter.generated.h"

UCLASS(config=Game)
class AMenuSystemCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	AMenuSystemCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	// Pointer to the online session interface.
	IOnlineSessionPtr OnlineSessionInterface;

protected:
	/** Called via input to create an online game session. */
	UFUNCTION(BlueprintCallable)
	void CreateGameSession();

	/** Called via input to join an online game session. */
	UFUNCTION(BlueprintCallable)
	void JoinGameSession();

	/** 
	 * Called on create session complete. 
	 * @param SessionName	Name of the online game session.
	 * @param bWasSuccessful	Did the online game session creation was successful.
	 */
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	/**
	 * Called on find sessions complete.
	 * @param bWasSuccessful	Did the online game sessions finding was successful.
	 */
	void OnFindSessionsComplete(bool bWasSuccessful);

	/**
	 * Called on join session complete.
	 * @param SessionName	Name of the online game session.
	 * @param Result	Result type of the join session event.
	 */
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

private:
	/** Event fired on create session complete event. */
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;

	/** Event fired on find sessions complete event. */
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;

	/** Event fired on join session complete event. */
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;

	// Pointer to the online session search object.
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
};

