// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UShooterAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
    if (ShooterCharacter == nullptr) 
    {
        ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
    }
    if (ShooterCharacter)
    {
        // Get the lateral speed of the character from velocity
        FVector Velocity{ ShooterCharacter->GetVelocity() };
        Velocity.Z = 0;
        Speed = Velocity.Size();

        // Is the character in the air?
        bIsInAir = ShooterCharacter->GetCharacterMovement()->IsFalling();

        // Is the character accelerating?
        if (ShooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f)
        {
            bIsAccelerating = true;
        }
        else
        {
            bIsAccelerating = false;
        }

        /** our aim rotation */
        FRotator AimRotation = ShooterCharacter->GetBaseAimRotation();
        /*
        FString RotationMessage = FString::Printf(TEXT("Base aim rotation: %f"), AimRotation.Yaw);
        */

        FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(ShooterCharacter->GetVelocity());
        /*
        FString MovementRotationMessage = FString::Printf(TEXT("Movement rotation: %f"), MovementRotation.Yaw);
        */

        MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(
            MovementRotation,
            AimRotation
        ).Yaw;
        /*
        FString OffssetMessage = FString::Printf(TEXT("Movement offset yaw: %f"), MovementOffsetYaw);

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::White, OffssetMessage);
        }
        */
    }
}

void UShooterAnimInstance::NativeInitializeAnimation()
{
    ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
}
