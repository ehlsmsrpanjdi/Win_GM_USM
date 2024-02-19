#pragma once
#include "PhysicsActor.h"


// Ό³Έν :
class Block : public PhysicsActor
{
public:
	// constrcuter destructer
	Block();
	~Block();

	// delete Function
	Block(const Block& _Other) = delete;
	Block(Block&& _Other) noexcept = delete;
	Block& operator=(const Block& _Other) = delete;
	Block& operator=(Block&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void StateUpdate(float _DeltaTime) override;
	void SetBoxState(BlockState _BlockState);
	void BoxCollisionEvent(BlockState _BlockState);

	void ItemStart();
	void NoneStart();

	BlockState State = BlockState::Item;
private:

};

