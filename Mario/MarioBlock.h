#pragma once
#include "BlockBase.h"
#include "MarioHelper.h"

// Ό³Έν :
class MarioBlock : public BlockBase
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
private:

};

