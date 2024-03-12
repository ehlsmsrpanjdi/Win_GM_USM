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

	void SetItemBlockDefault(int _Count = 1, ItemState _Item = ItemState::Coin, BlockState _BlockState = BlockState::ItemBlock);
	void SetItemBrickDefault(int _Count = 1, ItemState _Item = ItemState::Coin, BlockState _BlockState = BlockState::ItemBrick);
	void SetBrickDefault();
	BlockState GetState();

protected:
	virtual void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void StateUpdate(float _DeltaTime);

	void ItemBlockStart();
	void BrickStart();
	void ItemBrickStart();
	void InteractiveStart();
	void DefaultStart();

	void Interactive(float _DeltaTime);

	bool IsInit = false;
	virtual void BlockInit();
	
	FVector DefaultLocation = {};

	float DeltaTime = -0.1f;
	float UpForce = -2.f;
	float DownForce = 18.f;
	BlockState BoxState = BlockState::None;
	BlockState StartState = BlockState::None;

	int ItemCount=0;
	ItemState HaveItem = ItemState::None;

	bool Interacting = false;

	bool IsGround = false;

private:

};

