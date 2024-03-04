#pragma once
#include "PhysicsActor.h"
// Ό³Έν :
class GroundCoin : public PhysicsActor
{
public:
	// constrcuter destructer
	GroundCoin();
	~GroundCoin();

	// delete Function
	GroundCoin(const GroundCoin& _Other) = delete;
	GroundCoin(GroundCoin&& _Other) noexcept = delete;
	GroundCoin& operator=(const GroundCoin& _Other) = delete;
	GroundCoin& operator=(GroundCoin&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

};

