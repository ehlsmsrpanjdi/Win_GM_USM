#pragma once
#include "MonsterGoomba.h"
// Ό³Έν :
class GroundGoomba : public MonsterGoomba
{
public:
	// constrcuter destructer
	GroundGoomba();
	~GroundGoomba();

	// delete Function
	GroundGoomba(const GroundGoomba& _Other) = delete;
	GroundGoomba(GroundGoomba&& _Other) noexcept = delete;
	GroundGoomba& operator=(const GroundGoomba& _Other) = delete;
	GroundGoomba& operator=(GroundGoomba&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
private:

};

