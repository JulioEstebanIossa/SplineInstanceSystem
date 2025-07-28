#include "Components/SplineInstantiatorCompBase.h"
#include "Components/SplineComponent.h"
#include "Types/SplineInstanceSystemTypes.h"

USplineInstantiatorCompBase::USplineInstantiatorCompBase()
{
	PrimaryComponentTick.bCanEverTick = false;
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
}

void USplineInstantiatorCompBase::Instantiate()
{
#pragma region ValidateInstantiationSettings
	bool bCanInstantiate = true;

	if (InstantiationSettings.ForwardAxis == EOrientationAxis::None)
	{
		UE_LOG(LogSplineInstantiator, Error,
			TEXT("[%s] InstantiationSettings.ForwardAxis is None."),
			*GetName());
		bCanInstantiate = false;
	}

	if (InstantiationSettings.UpAxis == EOrientationAxis::None)
	{
		UE_LOG(LogSplineInstantiator, Error,
			TEXT("[%s] InstantiationSettings.UpAxis is None."),
			*GetName());
		bCanInstantiate = false;
	}

	if (InstantiationSettings.InstantiationMethod == ESplineInstantiationMethod::None)
	{
		UE_LOG(LogSplineInstantiator, Error,
			TEXT("[%s] InstantiationMethod is None."),
			*GetName());
		bCanInstantiate = false;
	}

	if (!bCanInstantiate)
	{
		return; 
	}
#pragma endregion 

	if (InstantiationSettings.InstantiationMethod == ESplineInstantiationMethod::InstanceCount_AdjustSpline)
	{
		// Adjust spline.
	}

	// Generates a new instance for each needed section count.
	for (int32 i = 0; i < GetSectionsCount(); i++)
	{	
		// The starting position of the current segment coincides with the ending position of the previous segment.
		const float StartDistance = i * InstantiationSettings.SectionLength;
		
		// The ending position of the current segment coincides with the starting position of the next segment.
		const float EndDistance = (i + 1) * InstantiationSettings.SectionLength;
		
		// Starting and Ending positions are calculated in local-space!!
		const ESplineCoordinateSpace::Type CoordinateSpace = ESplineCoordinateSpace::Type::Local;

		// Calculate the current segment along the spline.
		const FVector StartPosition = Spline->GetLocationAtDistanceAlongSpline(StartDistance, CoordinateSpace);
		
		const FVector StartTangent = Spline->GetTangentAtDistanceAlongSpline(StartDistance, CoordinateSpace)
			.GetClampedToMaxSize(InstantiationSettings.SectionLength); // Tangents are clamped to SectionLenght
		
		const FVector EndPosition = Spline->GetLocationAtDistanceAlongSpline(EndDistance, CoordinateSpace);
		
		const FVector EndTangent = Spline->GetTangentAtDistanceAlongSpline(EndDistance, CoordinateSpace)
			.GetClampedToMaxSize(InstantiationSettings.SectionLength); // Tangents are clamped to SectionLenght

		// Each child class will implement its own version of the method.
		UObject* Instance = GenerateInstance(FSplineSegmentInfo{ StartPosition, StartTangent, EndPosition, EndTangent });
		Instances.Add(Instance);
	}
}

void USplineInstantiatorCompBase::ClearInstances()
{
	for (int32 i = 0; i < Instances.Num(); i++)
	{	
		// Each child class will implement its own version of the method.
		DestroyInstance(Instances[i]);
	}
	Instances.Empty();
}

void USplineInstantiatorCompBase::BeginPlay()
{
	Super::BeginPlay();
}

int32 USplineInstantiatorCompBase::GetSectionsCount() const
{
	// The maximum number of sections that fit inside the spline.
	const int32 SplineMaxSections = static_cast<int32>(Spline->GetSplineLength() / InstantiationSettings.SectionLength);

	switch (InstantiationSettings.InstantiationMethod)
	{
	case ESplineInstantiationMethod::InstanceCount_SplineClamp:
		return FMath::Min(InstantiationSettings.InstanceCount, SplineMaxSections);

	case ESplineInstantiationMethod::InstanceCount_AdjustSpline:
		return InstantiationSettings.InstanceCount;

	case ESplineInstantiationMethod::FillSpline:
		return SplineMaxSections;

	case ESplineInstantiationMethod::None:
	default:
		return -1;
	}
}
