// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Characters/Eve.h" 
#include "Items.generated.h"

class USphereComponent;

UCLASS()
class STEALTHGAME_API AItems : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItems();

	virtual void OnPickup(AEve* Player);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	bool bIsOverlapping;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE bool IsOverlapping() const { return bIsOverlapping; }

	void DestroyItem();

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
