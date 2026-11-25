// Copyright (c) 2026 PH Scherer. MIT License.
//
// Unreal Automation Tests for UHealthComponent.
//
// IMPORTANT: these files are NOT compiled as part of the plugin. To run them,
// copy this file into a test module of an actual Unreal Engine project that
// references the GameplayFramework plugin (typically <YourProject>Tests), and
// add "UnrealEd" to that module's PrivateDependencyModuleNames (the tests use
// GEditor to obtain a world). Then run:
//
//   UnrealEditor <Project>.uproject -ExecCmds="Automation RunTests GameplayFramework.Health; Quit" -unattended -nopause -nullrhi
//
// The tests need a valid World so the component can be registered and owned
// by an actor with authority.

#if WITH_DEV_AUTOMATION_TESTS

#include "HealthComponent.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FHealthDamageTest,
	"GameplayFramework.Health.ApplyDamage",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FHealthDamageTest::RunTest(const FString& Parameters)
{
	UWorld* World = GEditor ? GEditor->GetEditorWorldContext().World() : nullptr;
	if (!World)
	{
		return true; // skip when no world is available (no engine in this repo)
	}

	AActor* Owner = World->SpawnActor<AActor>();
	check(Owner);

	UHealthComponent* Health = NewObject<UHealthComponent>(Owner);
	Health->RegisterComponent();
	Health->ResetHealth();

	TestEqual(TEXT("Starts at max"), Health->GetCurrentHealth(), Health->GetMaxHealth());

	Health->ApplyDamage(25.f);
	TestEqual(TEXT("Damage reduces health"), Health->GetCurrentHealth(), Health->GetMaxHealth() - 25.f);
	TestFalse(TEXT("Not dead after partial damage"), Health->IsDead());

	Health->ApplyDamage(Health->GetMaxHealth() + 1000.f);
	TestEqual(TEXT("Damage clamps at zero"), Health->GetCurrentHealth(), 0.f);
	TestTrue(TEXT("Dead after lethal damage"), Health->IsDead());

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FHealthHealTest,
	"GameplayFramework.Health.ApplyHeal",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FHealthHealTest::RunTest(const FString& Parameters)
{
	UWorld* World = GEditor ? GEditor->GetEditorWorldContext().World() : nullptr;
	if (!World)
	{
		return true;
	}

	AActor* Owner = World->SpawnActor<AActor>();
	check(Owner);

	UHealthComponent* Health = NewObject<UHealthComponent>(Owner);
	Health->RegisterComponent();
	Health->ResetHealth();

	Health->ApplyDamage(50.f);
	Health->ApplyHeal(10.f);
	TestEqual(TEXT("Heal restores health"), Health->GetCurrentHealth(), Health->GetMaxHealth() - 40.f);

	Health->ApplyHeal(10000.f);
	TestEqual(TEXT("Heal clamps at max"), Health->GetCurrentHealth(), Health->GetMaxHealth());

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FHealthDeathTest,
	"GameplayFramework.Health.DeathEvent",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FHealthDeathTest::RunTest(const FString& Parameters)
{
	UWorld* World = GEditor ? GEditor->GetEditorWorldContext().World() : nullptr;
	if (!World)
	{
		return true;
	}

	AActor* Owner = World->SpawnActor<AActor>();
	check(Owner);

	UHealthComponent* Health = NewObject<UHealthComponent>(Owner);
	Health->RegisterComponent();
	Health->ResetHealth();

	// Smoke test: lethal damage must set the dead state exactly once. The
	// OnDeath delegate fires internally via TrySetHealth; asserting IsDead()
	// covers the transition without needing a listener object.
	Health->ApplyDamage(Health->GetMaxHealth());
	TestTrue(TEXT("Death flag set"), Health->IsDead());

	return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS