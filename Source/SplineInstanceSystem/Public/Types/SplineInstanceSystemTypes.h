#pragma once

#include "CoreMinimal.h"
#include "SplineInstanceSystemTypes.generated.h"

/**
 * @brief The axis used to determine how an object is oriented/aligned when instantiated along a spline.
 */
UENUM(BlueprintType)
enum class EOrientationAxis : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Y = 2	 UMETA(DisplayName = "Y"),
	Z = 3	 UMETA(DisplayName = "Z"),
	X = 1	 UMETA(DisplayName = "X"),
	nX = 4   UMETA(DisplayName = "-X"),
	nY = 5   UMETA(DisplayName = "-Y"),
	nZ = 6   UMETA(DisplayName = "-Z")
};

class FOrientationAxisHelpers
{
public:
	/**
	 * @brief Returns the axis opposite to the given one.
	 */
	FORCEINLINE static EOrientationAxis GetOppositeAxis(EOrientationAxis InAxis)
	{
		switch (InAxis)
		{
		case EOrientationAxis::X:
			return EOrientationAxis::nX;

		case EOrientationAxis::Y:
			return EOrientationAxis::nY;

		case EOrientationAxis::Z:
			return EOrientationAxis::nZ;

		case EOrientationAxis::nX:
			return EOrientationAxis::X;

		case EOrientationAxis::nY:
			return EOrientationAxis::Y;

		case EOrientationAxis::nZ:
			return EOrientationAxis::Z;

		default:
			return EOrientationAxis::None;
		}
	}

	/**
	 * @brief Returns the display names of the given EOrientationAxis list.
	 */
	static TArray<TSharedPtr<FString>> GetDisplayNames(const TArray<EOrientationAxis>& Source)
	{
		if (UEnum* Enum = StaticEnum<EOrientationAxis>())
		{
			TArray<TSharedPtr<FString>> DisplayNames;
			for (int32 i = 0; i < Source.Num(); i++)
			{
				uint8 CurrentSourceValue = static_cast<uint8>(Source[i]);
				DisplayNames.Add(MakeShared<FString>(Enum->GetNameStringByValue(CurrentSourceValue)));
			}
			return DisplayNames;
		}
		return TArray<TSharedPtr<FString>>();
	}
};

UENUM(BlueprintType)
enum class ESplineInstantiationMethod : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	
	/* Generates a fixed number of instances. 
	If the total length of the instances to be generated exceeds the length of the spline, the excess instances will not be generated. */
	InstanceCount_SplineClamp = 1 UMETA(DisplayName = "Instance Count (SplineClamp)"),

	/* Generates a fixed number of instances. 
	If the total length of the instances to be generated exceeds the length of the spline, the spline is stretched to accommodate them all. */
	InstanceCount_AdjustSpline = 2 UMETA(DisplayName = "Instance Count (AdjustSpline)"),

	/* Generates enough instances to fill the entire length of the spline, respecting the specified SectionLength (see SplineInstantiationInfo.h). */
	FillSpline = 3 UMETA(DisplayName = "Fill Spline")
};
