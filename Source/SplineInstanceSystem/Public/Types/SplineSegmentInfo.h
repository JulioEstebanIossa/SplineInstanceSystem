#pragma once

#include "CoreMinimal.h"
#include "SplineSegmentInfo.generated.h"

/**
 * @brief Represents a spline segment, including an incoming and outgoing tangent. 
 * 
 * Useful for instantiating objects along splines.
 */
USTRUCT(BlueprintType)
struct FSplineSegmentInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartPosition = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartTangent = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EndPosition = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EndTangent = FVector::ZeroVector;

	FSplineSegmentInfo() = default;

	FSplineSegmentInfo(const FVector& InStartPosition, const FVector& InStartTangent, const FVector& InEndPosition, const FVector& InEndTangent)
	: StartPosition(InStartPosition), StartTangent(InStartTangent), EndPosition(InEndPosition), EndTangent(InEndTangent) { }
};

