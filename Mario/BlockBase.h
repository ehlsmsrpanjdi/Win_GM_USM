#pragma once
#include "PhysicsActor.h"
#include "MarioHelper.h"

// Ό³Έν :
class BlockBase : public PhysicsActor
{
public:
	// constrcuter destructer
	BlockBase();
	~BlockBase();

	// delete Function
	BlockBase(const BlockBase& _Other) = delete;
	BlockBase(BlockBase&& _Other) noexcept = delete;
	BlockBase& operator=(const BlockBase& _Other) = delete;
	BlockBase& operator=(BlockBase&& _Other) noexcept = delete;

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
	void InteractiveStart();


	void Item(float _DeltaTime);
	void Brick(float _DeltaTime);
	void None(float _DeltaTime);
	void Break(float _DeltaTime);
	void Interactive(float _DeltaTime);

	BlockState State = BlockState::Item;

	FVector DefaultLocation = {};

	float DeltaTime = -0.1f;
	float UpForce = -2.f;
	float DownForce = 18.f;
	BlockState StartState = BlockState::None;
	int ItemCount;

private:

};

