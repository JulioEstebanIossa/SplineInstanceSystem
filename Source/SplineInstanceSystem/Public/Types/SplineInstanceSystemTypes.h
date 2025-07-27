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
	
	/* Fill spline with a fixed number of instances. */
	InstanceCount_FillSpline = 1 UMETA(DisplayName = "Instance Count (FillSpline)"),

	/* Adjust spline length dynamically based on instance count. */
	InstanceCount_AdjustSpline = 2 UMETA(DisplayName = "Instance Count (AdjustSpline)"),

	/* Fill spline with a dynamic number of instances. (based on SectionLenght - see SplinePlacementSettings.h) */
	FillSpline = 3 UMETA(DisplayName = "Fill Spline")
};
