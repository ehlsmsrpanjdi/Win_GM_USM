#pragma once
#include "MarioBrick.h"
// Ό³Έν :
class GroundBrick : public MarioBrick
{
public:
	// constrcuter destructer
	GroundBrick();
	~GroundBrick();

	// delete Function
	GroundBrick(const GroundBrick& _Other) = delete;
	GroundBrick(GroundBrick&& _Other) noexcept = delete;
	GroundBrick& operator=(const GroundBrick& _Other) = delete;
	GroundBrick& operator=(GroundBrick&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
private:

};

