#pragma once
#include "MarioBlock.h"
#include "MarioHelper.h"


// Ό³Έν :
class MarioBrick : public BlockBase
{
public:
	// constrcuter destructer
	MarioBrick();
	~MarioBrick();

	// delete Function
	MarioBrick(const MarioBrick& _Other) = delete;
	MarioBrick(MarioBrick&& _Other) noexcept = delete;
	MarioBrick& operator=(const MarioBrick& _Other) = delete;
	MarioBrick& operator=(MarioBrick&& _Other) noexcept = delete;

protected:
	virtual void BeginPlay() override;
	void BlockInit() override;
private:

};

