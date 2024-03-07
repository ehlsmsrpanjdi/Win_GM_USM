#pragma once
#include "MarioBlock.h"
// Ό³Έν :
class GroundBlock : public MarioBlock
{
public:
	// constrcuter destructer
	GroundBlock();
	~GroundBlock();

	// delete Function
	GroundBlock(const GroundBlock& _Other) = delete;
	GroundBlock(GroundBlock&& _Other) noexcept = delete;
	GroundBlock& operator=(const GroundBlock& _Other) = delete;
	GroundBlock& operator=(GroundBlock&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
private:

};

