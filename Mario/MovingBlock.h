#pragma once
#include "PhysicsActor.h"

// Ό³Έν :
class MovingBlock : public PhysicsActor
{
public:
	// constrcuter destructer
	MovingBlock();
	~MovingBlock();

	// delete Function
	MovingBlock(const MovingBlock& _Other) = delete;
	MovingBlock(MovingBlock&& _Other) noexcept = delete;
	MovingBlock& operator=(const MovingBlock& _Other) = delete;
	MovingBlock& operator=(MovingBlock&& _Other) noexcept = delete;

	void MovingBlockInit(FVector _StartPos, FVector _EndPos, bool _IsTelePort);
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void Moving(float _DeltaTime);
	void CollisionEvent(float _DeltaTime);

	FVector StartPos = {};
	FVector EndPos = {};
	float Speed = 200.f;
	FVector CurSpeed = {};
	float MaxSpeed = 200.f;
	bool TelePort = false;
private:

};

