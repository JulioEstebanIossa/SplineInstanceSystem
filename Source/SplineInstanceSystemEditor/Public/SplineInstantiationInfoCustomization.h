#pragma once

#include "IPropertyTypeCustomization.h"

enum class EOrientationAxis : uint8;

/**
 * @brief Customization for FSplineInstantiationInfo
 * 
 * Manage UpAxis dropdown menu based on ForwardAxis selected value.
 */
class FSplineInstantiationInfoCustomization : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;

	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;

private:
	TArray<TSharedPtr<FString>> UpAxisComboBoxOptions;

	/**
	 * @brief Returns a list of EOrientationAxis display names filtered by the ForwardAxis selected value.
	 * @param ForwardAxisHandle The handle for ForwardAxis property.
	 * @param UpAxisHandle The handle for ForwardAxis property.
	 */
	TArray<EOrientationAxis> FilterUpAxisOptions(TSharedPtr<IPropertyHandle> ForwardAxisHandle, TSharedPtr<IPropertyHandle> UpAxisHandle);

	/**
	 * @brief Check if UpAxis property has a value compatible with the ForwardAxis one. If it is not, resets the UpAxis value.
	 * @param UpAxisHandle The handle for UpAxis property.
	 * @param UpAxisValidValues List of EOrientationAxis display names filtered by the ForwardAxis selected value.
	 */
	void ValidateUpAxisValue(TSharedPtr<IPropertyHandle> UpAxisHandle, const TArray<EOrientationAxis>& UpAxisValidValues);

	/**
	 * @brief Set UpAxis property value to None.
	 * @param UpAxisHandle The handle for UpAxis property.
	 */
	void ResetUpAxisValue(TSharedPtr<IPropertyHandle> UpAxisHandle);

	void CreateUpAxisCustomView(IDetailChildrenBuilder& ChildBuilder, 
		TSharedPtr<IPropertyHandle> ForwardAxisHandle, TSharedPtr<IPropertyHandle> UpAxisHandle, 
		const TArray<EOrientationAxis>& UpAxisValidValues);
};
