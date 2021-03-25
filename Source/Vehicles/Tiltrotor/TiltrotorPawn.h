#pragma once

#include "GameFramework/RotatingMovementComponent.h"

#include <memory>
#include "PIPCamera.h"
#include "common/common_utils/Signal.hpp"
#include "common/common_utils/UniqueValueMap.hpp"
#include "TiltrotorPawnEvents.h"

#include "TiltrotorPawn.generated.h"

UCLASS()
class AIRSIM_API ATiltrotorPawn : public APawn
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debugging")
    float RotatorFactor = 1.0f;

    ATiltrotorPawn();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation,
        FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

    //interface
    void initializeForBeginPlay();
    const common_utils::UniqueValueMap<std::string, APIPCamera*> getCameras() const;
    TiltrotorPawnEvents* getPawnEvents()
    {
        return &pawn_events_;
    }
    //called by API to set rotor speed
    void setRotorSpeed(const std::vector<TiltrotorPawnEvents::RotorTiltableInfo>& rotor_infos);


private: //variables
    //Unreal components
    static constexpr size_t rotor_count = 2;
    UPROPERTY() APIPCamera* camera_front_left_;
    UPROPERTY() APIPCamera* camera_front_right_;
    UPROPERTY() APIPCamera* camera_front_center_;
    UPROPERTY() APIPCamera* camera_back_center_;
    UPROPERTY() APIPCamera* camera_bottom_center_;

    UPROPERTY() URotatingMovementComponent* rotating_movements_[rotor_count];

    static constexpr size_t rotor_actuator_count = 2;
    UPROPERTY() UStaticMeshComponent* rotor_actuators_[rotor_actuator_count];

    TiltrotorPawnEvents pawn_events_;
};
