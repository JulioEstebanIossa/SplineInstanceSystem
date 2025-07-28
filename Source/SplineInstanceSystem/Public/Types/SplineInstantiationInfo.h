#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SplineInstanceSystemTypes.h"
#include "SplineInstantiationInfo.generated.h"

/**
 * @brief Parameters for object placement along a spline.
 */
USTRUCT(BlueprintType)
struct FSplineInstantiationInfo
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
	ESplineInstantiationMethod InstantiationMethod = ESplineInstantiationMethod::FillSpline;

	/* The number of objects to instantiate along the spline. 
	Only used if InstantiationMethod is set to an InstanceCount mode. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InstanceCount = 0;

	/* The length of each section whitch the spline will be sliced in. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SectionLength = 100.0f;

	/* Distance between instances. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Spacing = 0.0f;

	/* Instantiated object mobility (Static, Stationary, Movable). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EComponentMobility::Type> Mobility = EComponentMobility::Static;

	FSplineInstantiationInfo() = default;

	FSplineInstantiationInfo(EOrientationAxis InForwardAxis, EOrientationAxis InUpAxis, ESplineInstantiationMethod InInstantiationMethod, int32 InInstanceCount = 0,
		float InSectionLenght = 100.0F, float InSpacing = 0.0F, EComponentMobility::Type InMobility = EComponentMobility::Type::Static)
		: ForwardAxis(InForwardAxis), UpAxis(InUpAxis), InstantiationMethod(InInstantiationMethod), InstanceCount(InInstanceCount),
		SectionLength(InSectionLenght), Spacing(InSpacing), Mobility(InMobility) { }
};

