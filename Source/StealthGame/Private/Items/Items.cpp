// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Items.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Characters/Eve.h" 

// Sets default values
AItems::AItems()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    PrimaryActorTick.bCanEverTick = false;

    ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = ItemMesh;

    Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
    Sphere->SetupAttachment(RootComponent);
    Sphere->SetSphereRadius(100.f);

    bIsOverlapping = false;
}

// Called when the game starts or when spawned
void AItems::BeginPlay()
{
	Super::BeginPlay();
	
    Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItems::OnSphereOverlap);
    Sphere->OnComponentEndOverlap.AddDynamic(this, &AItems::OnSphereEndOverlap);
}

void AItems::OnPickup(AEve* Player)
{
    Destroy();
}

// Called every frame
void AItems::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItems::DestroyItem()
{
	Destroy();
}

void AItems::OnSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (AEve* Eve = Cast<AEve>(OtherActor))
    {
        bIsOverlapping = true;
    }
}

void AItems::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (AEve* Eve = Cast<AEve>(OtherActor))
    {
        bIsOverlapping = false;
    }
}

