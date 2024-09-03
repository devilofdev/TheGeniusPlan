// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/IHttpRequest.h"
#include "LoginWidget.generated.h"

/**
 *
 */
UCLASS()
class THEGENIUSPLAN_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void ClickedLogin();

	UFUNCTION(BlueprintCallable)
	void ClickedQuit();

	UFUNCTION(BlueprintCallable)
	void ClickedSignUp();

	UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	TObjectPtr<class AEntryHUD> EntryHUD;

protected:
	void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ButtonLogin;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ButtonSignUp;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ButtonQuit;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UEditableTextBox> EditableTextID;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UEditableTextBox> EditableTextPassword;
};
