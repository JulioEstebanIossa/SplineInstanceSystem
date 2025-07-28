#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/SplineInstantiationInfo.h"
#include "Types/SplineSegmentInfo.h"
#include "SplineInstantiatorCompBase.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogSplineInstantiator, Log, All);

class USplineComponent;

UCLASS(Abstract)
class SPLINEINSTANCESYSTEM_API USplineInstantiatorCompBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	/* Foundamental parameters for object placement along a spline. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SplineInstantiationSystem")
	FSplineInstantiationInfo InstantiationSettings;

protected:
	/* The main spline along which objects will be placed. */
	UPROPERTY(BlueprintReadOnly, Category = "SplineInstantiationSystem")
	USplineComponent* Spline;

	/* The objects instantiated by this component. */
	UPROPERTY(BlueprintReadOnly, Category = "SplineInstantiationSystem")
	TArray<UObject*> Instances;

public:
	USplineInstantiatorCompBase();

	/**
	 * @brief Generates instances along the spline based on the selected InstantiationMethod.
	 */
	void Instantiate();

	/**
	 * @brief Delete all generated instances.
	 */
	void ClearInstances();

protected:
	virtual void BeginPlay() override;

	/**
	 * @brief Returns the number of sections the spline will be divided into, based on the InstantiationMethod.
	 */
	UFUNCTION(BlueprintCallable, Category = "SplineInstantiationSystem")
	FORCEINLINE int32 GetSectionsCount() const;

	/**
	 * @brief Generates an object along the spline, positioned according to the given segment and aligned according to the InstantiationSettings. 
	 * 
	 * Child classes must override this function to specify their own behavior.
	 * @param SplineSegment The spline segment along which the generated object will be positioned.
	 * @return The generated object.
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "SplineInstantiationSystem")
	UObject* GenerateInstance(const FSplineSegmentInfo& SplineSegment);
	virtual UObject* GenerateInstance_Implementation(const FSplineSegmentInfo& SplineSegment) { return nullptr; }

	/**
	 * @brief Destroys the given instance.
	 *
	 * Child classes must override this function to specify their own behavior.
	 * @param Instance The instance to destroy.
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "SplineInstantiationSystem")
	void DestroyInstance(UObject* Instance);
	virtual void DestroyInstance_Implementation(UObject* Instance) { }
};
