// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include <iostream>
#include <sstream>

#include "BlockbreakerWorldSettings.h"
/*
#define _CLASS_FUNC (*FString(__FUNCTION__))
#define _CLASS (*FString(__FUNCTION__).Left(*FString(__FUNCTION__).Find(TEXT(":"))) )
#define _FUNC (*FString(__FUNCTION__).Right(*FString(__FUNCTION__).Len() - *FString(__FUNCTION__).Find(TEXT("::")) - 2 ))
#define _LINE (*FString::FromInt(__LINE__))
#define _FUNCSIG (*FString(__FUNCSIG__))  
#define _CLASS_LINE (_CLASS + "(" + _LINE + ")" )

#define VMSG(Param1) (GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *(_CLASS_LINE + ": " + Param1)) )
#define VMSG2(Param1, Param2) (GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *(_CLASS_LINE + ": " + Param1 + " " + Param2)) )
#define VMSGF(Param1,Param2) (GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *(_CLASS_LINE + ": " + Param1 + " " + *FString::SanitizeFloat(Param2))) )

#define LOG(LogCat, Param1) 		UE_LOG(LogCat,Warning,TEXT("%s: %s"), *_CLASS_LINE, *FString(Param1))
#define LOG2(LogCat, Param1,Param2) 	UE_LOG(LogCat,Warning,TEXT("%s: %s %s"), *_CLASS_LINE, *FString(Param1),*FString(Param2))
#define LOGF(LogCat, Param1,Param2) 	UE_LOG(LogCat,Warning,TEXT("%s: %s %f"), *_CLASS_LINE, *FString(Param1),Param2)
#define LOGM(LogCat, FormatString , ...) UE_LOG(LogCat,Warning,TEXT("%s: %s"), 	*_CLASS_LINE, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__ ) )
*/