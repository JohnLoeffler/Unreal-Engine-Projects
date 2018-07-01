// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blockbreaker.h"
#include "Blueprint/UserWidget.h"
#include "MenuController.generated.h"

class UMainMenuWidget;

UCLASS()
class BLOCKBREAKER_API AMenuController : public APlayerController
{
  GENERATED_BODY()
public:
  AMenuController();
  virtual ~AMenuController() {}

  virtual void BeginPlay() override;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu Widgets")
    TSubclassOf<UUserWidget> wMainMenu;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu Widgets")
    UMainMenuWidget* MainMenu;


};
