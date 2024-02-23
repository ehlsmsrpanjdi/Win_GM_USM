#pragma once
#include "MonsterBase.h"

// Ό³Έν :
class MonsterGoomba : public MonsterBase
{
public:
	// constrcuter destructer
	MonsterGoomba();
	~MonsterGoomba();

	// delete Function
	MonsterGoomba(const MonsterGoomba& _Other) = delete;
	MonsterGoomba(MonsterGoomba&& _Other) noexcept = delete;
	MonsterGoomba& operator=(const MonsterGoomba& _Other) = delete;
	MonsterGoomba& operator=(MonsterGoomba&& _Other) noexcept = delete;

	void BeginPlay() override;

protected:

private:

};

