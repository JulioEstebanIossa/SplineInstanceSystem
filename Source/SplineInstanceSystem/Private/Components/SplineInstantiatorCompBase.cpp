#include "Components/SplineInstantiatorCompBase.h"
#include "Components/SplineComponent.h"
#include "Types/SplineInstanceSystemTypes.h"

USplineInstantiatorCompBase::USplineInstantiatorCompBase()
{
	PrimaryComponentTick.bCanEverTick = false;
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
}

void USplineInstantiatorCompBase::BeginPlay()
{
	Super::BeginPlay();
}

int32 USplineInstantiatorCompBase::GetSectionsCount()
{
	switch (InstantiationSettings.InstantiationMethod)
	{
	case ESplineInstantiationMethod::InstanceCount_FillSpline:
		break;

	case ESplineInstantiationMethod::InstanceCount_AdjustSpline:
		break;

	case ESplineInstantiationMethod::FillSpline:
		break;

	case ESplineInstantiationMethod::None:
	default:
		return -1;
	}
	return 0;
}
