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
	void SetItemCount(int _Count);
	void SetItemState(ItemState _Item);
	void SetBoxState(BlockState _MarioBlockState);
	void SetBoxStartState(BlockState _MarioBlockState);

protected:
	virtual void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void StateUpdate(float _DeltaTime) override;
	void BoxCollisionEvent(BlockState _MarioBlockState);


	void NoneStart();
	void ItemBlockStart();
	void BrickStart();
	void ItemBrickStart();
	void InteractiveStart();
	void DefaultStart();


	void None(float _DeltaTime);
	void ItemBlock(float _DeltaTime);
	void Brick(float _DeltaTime);
	void ItemBrick(float _DeltaTime);
	void Interactive(float _DeltaTime);
	void Default(float _DeltaTime);


	FVector DefaultLocation = {};

	float DeltaTime = -0.1f;
	float UpForce = -2.f;
	float DownForce = 18.f;
	BlockState BoxState = BlockState::None;
	BlockState StartState = BlockState::None;

	int ItemCount=0;
	ItemState HaveItem = ItemState::None;

	bool Interacting = false;

private:

};

