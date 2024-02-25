#pragma once
#include "PhysicsActor.h"
#include "MarioHelper.h"

// Ό³Έν :
class AFire : public PhysicsActor
{
public:
	AFire();
	~AFire();

	AFire(const AFire& _Other) = delete;
	AFire(AFire&& _Other) noexcept = delete;
	AFire& operator=(const AFire& _Other) = delete;
	AFire& operator=(AFire&& _Other) noexcept = delete;


	void SetDirState(EActorDir _DirState);

protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;

	void CollisionEvent(float _DeltaTime);
	void WallCheck(float _DeltaTime);

private:
	float Speed = 300.0f;
};

