// Copyright Epic Games, Inc. All Rights Reserved.

#include "SplineInstanceSystemEditor.h"
#include "Types/SplineInstantiationInfo.h"
#include "SplineInstantiationInfoCustomization.h"

#define LOCTEXT_NAMESPACE "FSplineInstanceSystemEditorModule"

void FSplineInstanceSystemEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	RegisterCustomizations();
}

void FSplineInstanceSystemEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	UnregisterCustomizations();
}

void FSplineInstanceSystemEditorModule::RegisterCustomizations()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	PropertyModule.RegisterCustomPropertyTypeLayout(
		"SplineInstantiationInfo", 
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FSplineInstantiationInfoCustomization::MakeInstance)
	);

	PropertyModule.NotifyCustomizationModuleChanged();
}

void FSplineInstanceSystemEditorModule::UnregisterCustomizations()
{
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomPropertyTypeLayout("SplineInstantiationInfo");
		PropertyModule.NotifyCustomizationModuleChanged();
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSplineInstanceSystemEditorModule, SplineInstanceSystemEditor)