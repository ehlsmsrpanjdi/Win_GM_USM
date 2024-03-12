#pragma once
#include "MonsterScore.h"
// Ό³Έν :
class ItemScore : public MonsterScore
{
public:
	// constrcuter destructer
	ItemScore();
	~ItemScore();

	// delete Function
	ItemScore(const ItemScore& _Other) = delete;
	ItemScore(ItemScore&& _Other) noexcept = delete;
	ItemScore& operator=(const ItemScore& _Other) = delete;
	ItemScore& operator=(ItemScore&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
private:

};

