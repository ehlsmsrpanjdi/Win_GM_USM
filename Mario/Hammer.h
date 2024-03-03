#pragma once
#include "PhysicsActor.h"
#include "MarioHelper.h"

class Koopa;
// Ό³Έν :
class Hammer : public PhysicsActor
{
public:
	// constrcuter destructer
	Hammer();
	~Hammer();

	// delete Function
	Hammer(const Hammer& _Other) = delete;
	Hammer(Hammer&& _Other) noexcept = delete;
	Hammer& operator=(const Hammer& _Other) = delete;
	Hammer& operator=(Hammer&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void CollisionEvent(float _DeltaTime);
private:

};

