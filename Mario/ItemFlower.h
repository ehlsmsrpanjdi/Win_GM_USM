#pragma once
#include "ItemBase.h"

// Ό³Έν :
class ItemFlower : public ItemBase
{
public:
	// constrcuter destructer
	ItemFlower();
	~ItemFlower();

	// delete Function
	ItemFlower(const ItemFlower& _Other) = delete;
	ItemFlower(ItemFlower&& _Other) noexcept = delete;
	ItemFlower& operator=(const ItemFlower& _Other) = delete;
	ItemFlower& operator=(ItemFlower&& _Other) noexcept = delete;

protected:

	void BeginPlay() override;

private:

};

