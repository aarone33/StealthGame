#include "Characters/Eve.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Items/Items.h"
#include "Items/Door.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

AEve::AEve()
{
    PrimaryActorTick.bCanEverTick = true;
    Health = 100.f;
}

void AEve::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            SubSystem->AddMappingContext(EveContext, 0);
        }
    }
}

void AEve::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AEve::Move(const FInputActionValue& Value)
{
    const FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwardDirection, MovementVector.Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
}

void AEve::Look(const FInputActionValue& Value)
{
    const FVector2D LookAxisValue = Value.Get<FVector2D>();
    if (GetController())
    {
        AddControllerYawInput(LookAxisValue.X);
        AddControllerPitchInput(LookAxisValue.Y);
    }
}

void AEve::EKeyPressed()
{
    TArray<AActor*> OverlappingActors;
    GetOverlappingActors(OverlappingActors);

    for (AActor* Actor : OverlappingActors)
    {
        if (AItems* Item = Cast<AItems>(Actor))
        {
            Item->OnPickup(this);
        }
        else if (ADoor* Door = Cast<ADoor>(Actor))
        {
            Door->TryOpen(this);
        }
    }
}

void AEve::Jump()
{
    Super::Jump();
}

void AEve::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AEve::Move);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AEve::Look);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AEve::Jump);
        EnhancedInputComponent->BindAction(EKeyPress, ETriggerEvent::Triggered, this, &AEve::EKeyPressed);
    }
}

float AEve::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    Health -= DamageAmount;

    if (Health <= 0.f)
    {
        if (GameOverWidgetClass)
        {
            GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
            if (GameOverWidget)
            {
                GameOverWidget->AddToViewport();

                if (APlayerController* PC = Cast<APlayerController>(GetController()))
                {
                    PC->SetShowMouseCursor(true);
                    PC->SetInputMode(FInputModeUIOnly());
                }
            }
        }

        DisableInput(Cast<APlayerController>(GetController()));
    }

    return DamageAmount;
}

void AEve::Landed(const FHitResult& Hit)
{
    Super::Landed(Hit);

    float FallVelocity = -GetCharacterMovement()->Velocity.Z;

    float SafeFallSpeed = 600.f;
    float FatalFallSpeed = 1200.f;

    if (FallVelocity > SafeFallSpeed)
    {
        float Damage = FMath::GetMappedRangeValueClamped(
            FVector2D(SafeFallSpeed, FatalFallSpeed),
            FVector2D(10.f, 100.f),
            FallVelocity
        );

        UGameplayStatics::ApplyDamage(this, Damage, GetController(), this, nullptr);
    }
}
