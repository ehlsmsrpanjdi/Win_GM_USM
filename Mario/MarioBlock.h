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
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void StateUpdate(float _DeltaTime) override;
	void SetBoxState(BlockState _MarioBlockState);
	void BoxCollisionEvent(BlockState _MarioBlockState);

	void ItemStart();
	void NoneStart();

	BlockState State = BlockState::Item;

	UImageRenderer* ColRenderer = nullptr;

private:

};

