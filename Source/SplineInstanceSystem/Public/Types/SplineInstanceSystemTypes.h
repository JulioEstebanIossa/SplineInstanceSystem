#pragma once

#include "CoreMinimal.h"

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
