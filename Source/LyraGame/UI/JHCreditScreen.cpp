// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JHCreditScreen.h"

#include "Input/CommonUIInputTypes.h"


void UJHCreditScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BackHandle = RegisterUIActionBinding(FBindUIActionArgs(BackInputActionData,true,FSimpleDelegate::CreateUObject(this,&ThisClass::HandleBackAction)));
	SlowHandle = RegisterUIActionBinding(FBindUIActionArgs(SlowInputActionData,true,FSimpleDelegate::CreateUObject(this,&ThisClass::HandleSlowAction)));
	FastHandle = RegisterUIActionBinding(FBindUIActionArgs(FastInputActionData,true,FSimpleDelegate::CreateUObject(this,&ThisClass::HandleFastAction)));
 

}

void UJHCreditScreen::HandleBackAction()
{
	DeactivateWidget();
}
