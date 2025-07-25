#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SplineInstanceSystemTypes.h"
#include "SplinePlacementSettings.generated.h"

/**
 * @brief Parameters for object placement along a spline.
 */
USTRUCT(BlueprintType)
struct FSplinePlacementSettings
{
	GENERATED_BODY()

	/* The axis used as forward vector when an object is instantiated along a spline. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EOrientationAxis ForwardAxis = EOrientationAxis::X;

	/* The axis used as up vector when an object is instantiated along a spline. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EOrientationAxis UpAxis = EOrientationAxis::Z;

	/* How objects should be instantiated along the spline. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESplineInstantiationMethod InstantiationMethod;

	/* The length of each section whitch the spline will be sliced in. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SectionLength = 100.0f;

	/* Distance between instances. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Spacing = 100.0f;

	/* Instantiated object mobility (Static, Stationary, Movable). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EComponentMobility::Type> Mobility = EComponentMobility::Static;

	FSplinePlacementSettings() = default;

	FSplinePlacementSettings(EOrientationAxis InForwardAxis, EOrientationAxis InUpAxis, ESplineInstantiationMethod InInstantiationMethod,
		float InSectionLenght, float InSpacing = 0.0F, EComponentMobility::Type InMobility = EComponentMobility::Type::Static)
		: ForwardAxis(InForwardAxis), UpAxis(InUpAxis), InstantiationMethod(InInstantiationMethod),
		SectionLength(InSectionLenght), Spacing(InSpacing), Mobility(InMobility) { }
};

