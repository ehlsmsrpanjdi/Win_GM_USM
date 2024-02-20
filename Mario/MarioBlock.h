#pragma once
#include "PhysicsActor.h"
#include "MarioHelper.h"

// Ό³Έν :
class MarioBlock : public PhysicsActor
{
public:
	// constrcuter destructer
	MarioBlock();
	~MarioBlock();

	// delete Function
	MarioBlock(const MarioBlock& _Other) = delete;
	MarioBlock(MarioBlock&& _Other) noexcept = delete;
	MarioBlock& operator=(const MarioBlock& _Other) = delete;
	MarioBlock& operator=(MarioBlock&& _Other) noexcept = delete;

protected:
	virtual void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void StateUpdate(float _DeltaTime) override;
	void SetBoxState(BlockState _MarioBlockState);
	void BoxCollisionEvent(BlockState _MarioBlockState);

	void ItemStart();
	void BrickStart();
	void NoneStart();
	void BreakStart();


	void Item(float _DeltaTime);
	void Brick(float _DeltaTime);
	void None(float _DeltaTime);
	void Break(float _DeltaTime);


	BlockState State = BlockState::Item;

	float DeltaTime = 0.f;
	float UpForce = -10.f;
	float DownForce = 50.f;


private:

};

