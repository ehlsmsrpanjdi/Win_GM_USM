#pragma once
#include "BrokenBrick.h"
// Ό³Έν :
class GroundBrokenBrick : public BrokenBrick
{
public:
	// constrcuter destructer
	GroundBrokenBrick();
	~GroundBrokenBrick();

	// delete Function
	GroundBrokenBrick(const GroundBrokenBrick& _Other) = delete;
	GroundBrokenBrick(GroundBrokenBrick&& _Other) noexcept = delete;
	GroundBrokenBrick& operator=(const GroundBrokenBrick& _Other) = delete;
	GroundBrokenBrick& operator=(GroundBrokenBrick&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

};

