// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "XenoCharacterAttributeSet.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AbilitySystemInterface.h"
#include "XenoLikeProjectCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class AXenoLikeProjectCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	//要らない
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	//USpringArmComponent* CameraBoom;

	/** Follow camera */
	//いらない
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	//UCameraComponent* FollowCamera;
	
protected:

	////全部要らないinput
	///** Jump Input Action */
	//UPROPERTY(EditAnywhere, Category="Input")
	//UInputAction* JumpAction;

	///** Move Input Action */
	//UPROPERTY(EditAnywhere, Category="Input")
	//UInputAction* MoveAction;

	///** Look Input Action */
	//UPROPERTY(EditAnywhere, Category="Input")
	//UInputAction* LookAction;

	///** Mouse Look Input Action */
	//UPROPERTY(EditAnywhere, Category="Input")
	//UInputAction* MouseLookAction;

public:

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystem;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	UXenoCharacterAttributeSet* XenoCharacterAttributeSet;

	/** Constructor */
	AXenoLikeProjectCharacter();	

protected:

	///** Initialize input action bindings */
	////要らない
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	////iraina 変更が必要
	///** Called for movement input */
	//void Move(const FInputActionValue& Value);

	///** Called for looking input */
	//void Look(const FInputActionValue& Value);

public:

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	////iranai
	///** Handles look inputs from either controls or UI interfaces */
	//UFUNCTION(BlueprintCallable, Category="Input")
	//virtual void DoLook(float Yaw, float Pitch);

	///** Handles jump pressed inputs from either controls or UI interfaces */
	//UFUNCTION(BlueprintCallable, Category="Input")
	//virtual void DoJumpStart();

	///** Handles jump pressed inputs from either controls or UI interfaces */
	//UFUNCTION(BlueprintCallable, Category="Input")
	//virtual void DoJumpEnd();

public:

	////全部要らない
	///** Returns CameraBoom subobject **/
	//FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	///** Returns FollowCamera subobject **/
	//FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

