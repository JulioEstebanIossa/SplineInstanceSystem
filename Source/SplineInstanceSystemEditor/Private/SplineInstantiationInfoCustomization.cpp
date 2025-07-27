#include "SplineInstantiationInfoCustomization.h"
#include "IDetailChildrenBuilder.h"

// Runtime module
#include "Types/SplineInstantiationInfo.h"
#include "Types/SplineInstanceSystemTypes.h"

// Slate 
#include "DetailWidgetRow.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Text/STextBlock.h"

#include "Fonts/SlateFontInfo.h"

#define LOCTEXT_NAMESPACE "SplineInstanceSystem"

TSharedRef<IPropertyTypeCustomization> FSplineInstantiationInfoCustomization::MakeInstance()
{
	return MakeShareable<FSplineInstantiationInfoCustomization>(new FSplineInstantiationInfoCustomization);
}

void FSplineInstantiationInfoCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	// Header doesn't need modifies.
	HeaderRow.NameContent()[StructPropertyHandle->CreatePropertyNameWidget()]
		.ValueContent()[StructPropertyHandle->CreatePropertyValueWidget()];
}

void FSplineInstantiationInfoCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	uint32 NumChildren;
	PropertyHandle->GetNumChildren(NumChildren);

	TSharedPtr<IPropertyHandle> ForwardAxisHandle = nullptr;
	TSharedPtr<IPropertyHandle> UpAxisHandle = nullptr;

	// Loops on all property children to catch Forward and Up axis properties.
	for (uint32 i = 0; i < NumChildren;	i++)
	{
		TSharedRef<IPropertyHandle> ChildHandle = PropertyHandle->GetChildHandle(i).ToSharedRef();

		if (FProperty* ChildProperty = ChildHandle->GetProperty())
		{
			// Check name of each child.
			FName ChildName = ChildProperty->GetFName();

			// Catch ForwardAxis.
			if (ChildName == GET_MEMBER_NAME_CHECKED(FSplineInstantiationInfo, ForwardAxis))
			{
				ForwardAxisHandle = ChildHandle;
				ChildBuilder.AddProperty(ChildHandle); // Add ForwardAxis property normally.
			}
			// Catch UpAxis.
			else if (ChildName == GET_MEMBER_NAME_CHECKED(FSplineInstantiationInfo, UpAxis))
			{
				UpAxisHandle = ChildHandle;
				TArray<EOrientationAxis> UpAxisValidValues = FilterUpAxisOptions(ForwardAxisHandle, UpAxisHandle);
				ValidateUpAxisValue(UpAxisHandle, UpAxisValidValues);
				CreateUpAxisCustomView(ChildBuilder, ForwardAxisHandle, UpAxisHandle, UpAxisValidValues); // Customize UpAxis property.
			}
			// Add other properties normally.
			else
			{
				ChildBuilder.AddProperty(ChildHandle);
			}
		}
	}
}

TArray<EOrientationAxis> FSplineInstantiationInfoCustomization::FilterUpAxisOptions(TSharedPtr<IPropertyHandle> ForwardAxisHandle, TSharedPtr<IPropertyHandle> UpAxisHandle)
{
	if (ForwardAxisHandle.IsValid() && UpAxisHandle.IsValid())
	{
		// Get ForwardAxis current value.
		uint8 ForwardAxisValue;
		ForwardAxisHandle->GetValue(ForwardAxisValue);
		EOrientationAxis ForwardAxis = static_cast<EOrientationAxis>(ForwardAxisValue);
		
		if (UEnum* Enum = StaticEnum<EOrientationAxis>())
		{
			TArray<EOrientationAxis> FilteredOptions;

			// Loops on all enum options.
			for (int32 i = 0; i < Enum->NumEnums() - 1; i++)
			{
				EOrientationAxis Candidate = static_cast<EOrientationAxis>(Enum->GetValueByIndex(i));

				// For each option check if it is candidable as UpVector.
				bool bAllow = false;
				if (ForwardAxis == EOrientationAxis::None)
				{
					bAllow = (Candidate == EOrientationAxis::None);
				}
				else if (Candidate != ForwardAxis && Candidate != FOrientationAxisHelpers::GetOppositeAxis(ForwardAxis))
				{
					bAllow = true;
				}

				// If the option is a valid candidate, add it to the filtered options array.
				if (bAllow)
				{
					FilteredOptions.Add(Candidate);
				}
			}

			return FilteredOptions;
		}
	}

	return TArray<EOrientationAxis>();
}

void FSplineInstantiationInfoCustomization::ValidateUpAxisValue(TSharedPtr<IPropertyHandle> UpAxisHandle, const TArray<EOrientationAxis>& UpAxisValidValues)
{
	if (UpAxisHandle.IsValid())
	{
		// Get UpdAxis current value.
		uint8 CurrentUpAxisValue;
		UpAxisHandle->GetValue(CurrentUpAxisValue);
		EOrientationAxis CurrentUpAxis = static_cast<EOrientationAxis>(CurrentUpAxisValue);

		// If the current UpAxis value is incompatible with the ForwardAxis one, resets it.
		if (!UpAxisValidValues.Contains(CurrentUpAxis))
		{
			ResetUpAxisValue(UpAxisHandle);
		}
	}
}

void FSplineInstantiationInfoCustomization::ResetUpAxisValue(TSharedPtr<IPropertyHandle> UpAxisHandle)
{
	if (UpAxisHandle.IsValid())
	{
		UpAxisHandle->SetValue(static_cast<uint8>(EOrientationAxis::None));
	}
}

void FSplineInstantiationInfoCustomization::CreateUpAxisCustomView(IDetailChildrenBuilder& ChildBuilder, 
	TSharedPtr<IPropertyHandle> ForwardAxisHandle, TSharedPtr<IPropertyHandle> UpAxisHandle, 
	const TArray<EOrientationAxis>& UpAxisValidValues)
{
	if (UEnum* Enum = StaticEnum<EOrientationAxis>())
	{
		TSharedPtr<SComboBox<TSharedPtr<FString>>> ComboBox;
		
		// Update ComboBox Options.
		UpAxisComboBoxOptions = FOrientationAxisHelpers::GetDisplayNames(UpAxisValidValues);

		ChildBuilder.AddCustomRow(LOCTEXT("UpAxis", "Up Axis"))
			.NameContent()
			[
				UpAxisHandle->CreatePropertyNameWidget()
			]
			.ValueContent()
			.MinDesiredWidth(105)
			[
				SAssignNew(ComboBox, SComboBox<TSharedPtr<FString>>)
					.OptionsSource(&UpAxisComboBoxOptions) // Setup ComboBox Options
					.OnGenerateWidget_Lambda([](TSharedPtr<FString> InOption)
						{
							return SNew(STextBlock)
								.Text(FText::FromString(*InOption))
								.Font(FEditorStyle::GetFontStyle("PropertyWindow.NormalFont"));
						})
					.OnSelectionChanged_Lambda([UpAxisHandle, Enum](TSharedPtr<FString> Selected, ESelectInfo::Type)
						{
							if (Selected.IsValid())
							{
								uint8 NewValue = Enum->GetValueByNameString(*Selected);
								UpAxisHandle->SetValue(NewValue);
							}
						})
					.InitiallySelectedItem(UpAxisComboBoxOptions.Num() > 0 ? UpAxisComboBoxOptions[0] : nullptr)
					[
						SNew(STextBlock)
							.Text_Lambda([UpAxisHandle, Enum]()
								{
									uint8 Value;
									UpAxisHandle->GetValue(Value);
									return Enum->GetDisplayNameTextByValue(Value);
								})
					]
			];

		// Set callback to update UpAxis when ForwardAxis changes.
		ForwardAxisHandle->SetOnPropertyValueChanged(FSimpleDelegate::CreateLambda([=]()
			{
				TArray<EOrientationAxis> UpAxisValidValues = FilterUpAxisOptions(ForwardAxisHandle, UpAxisHandle);

				// Revalidate UpAxis Options.
				ValidateUpAxisValue(UpAxisHandle, UpAxisValidValues);

				if (ComboBox.IsValid())
				{
					// Update ComboBox Options and rebuild it.
					UpAxisComboBoxOptions = FOrientationAxisHelpers::GetDisplayNames(UpAxisValidValues);
					ComboBox->RefreshOptions();
				}
			}));
	}
}

#undef LOCTEXT_NAMESPACE