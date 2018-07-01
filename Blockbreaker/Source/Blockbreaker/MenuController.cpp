// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuController.h"
#include "../Public/MainMenuWidget.h"
#include "Blueprint/UserWidget.h"

AMenuController::AMenuController() {
  
}

void AMenuController::BeginPlay() {
  Super::BeginPlay();
  if (wMainMenu) {
    MainMenu = CreateWidget<UMainMenuWidget>(this, wMainMenu);
    if (MainMenu) {
      MainMenu->AddToViewport();
    }
  }
  bShowMouseCursor = true;
}

