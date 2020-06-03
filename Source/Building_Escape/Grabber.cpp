// Copyright TB 2020


#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInputComponent();
}

void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{		
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Physics Handle found on %s"), *GetOwner()->GetName());
	}	
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{		
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}		
}

void UGrabber::Grab()
{

	UE_LOG(LogTemp, Warning, TEXT("grab pressed"));

	FVector PlayerVPLoc;
	FRotator PlayerVPRot;
	GetWorld()->GetFirstPlayerController()->GetActorEyesViewPoint(
		OUT PlayerVPLoc, 
		OUT PlayerVPRot
	);
	
	FVector LineTraceEnd = PlayerVPLoc + PlayerVPRot.Vector() * Reach;
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	if (HitResult.GetActor())
	{			
		PhysicsHandle->GrabComponentAtLocation
		(
			ComponentToGrab,
			NAME_None,
			LineTraceEnd
		);
		UE_LOG(LogTemp, Error, TEXT("Grabbed it"));
	}
	
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("rekease pressed"));	
	PhysicsHandle->ReleaseComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerVPLoc;
	FRotator PlayerVPRot;
	GetWorld()->GetFirstPlayerController()->GetActorEyesViewPoint(
		OUT PlayerVPLoc, 
		OUT PlayerVPRot
	);
	
	FVector LineTraceEnd = PlayerVPLoc + PlayerVPRot.Vector() * Reach;
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
	
}


FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{

	FHitResult Hit;
	// get player viewpoint
	FVector PlayerVPLoc;
	FRotator PlayerVPRot;
	GetWorld()->GetFirstPlayerController()->GetActorEyesViewPoint(
		OUT PlayerVPLoc, 
		OUT PlayerVPRot
	);
	
	FVector LineTraceEnd = PlayerVPLoc + PlayerVPRot.Vector() * Reach;

	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerVPLoc,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	AActor* ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ActorHit->GetName());
	}	

	return Hit;
}
