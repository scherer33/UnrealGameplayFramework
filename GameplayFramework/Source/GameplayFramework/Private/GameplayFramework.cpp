// Copyright (c) 2026 PH Scherer. MIT License.

#include "GameplayFramework.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogGameplayFramework);

IMPLEMENT_MODULE(FGameplayFrameworkModule, GameplayFramework);

void FGameplayFrameworkModule::StartupModule()
{
	UE_LOG(LogGameplayFramework, Log, TEXT("GameplayFramework module started."));
}

void FGameplayFrameworkModule::ShutdownModule()
{
	UE_LOG(LogGameplayFramework, Log, TEXT("GameplayFramework module shut down."));
}
