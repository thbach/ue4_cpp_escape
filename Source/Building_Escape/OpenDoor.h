// Copyright TB 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	void PlaySound();
	void FindAudioComponent();
	void FindPressurePlate();
	float TotalMassOfActors() const;

private:

	float InitialYaw;
	float CurrentYaw;
	
	UPROPERTY(EditAnywhere)
	float MassToOpenDoor = 50.f;
	
	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.f;

	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.f;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 2.f;
	
	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed = 4.f;	
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;		

	UAudioComponent* AudioComponent = nullptr;
			
};
