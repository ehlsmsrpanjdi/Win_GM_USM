#pragma once
#include "CollisionActor.h"
// Ό³Έν :
class Stage1_Map : public CollisionActor
{
public:
	// constrcuter destructer
	Stage1_Map();
	~Stage1_Map();

	// delete Function
	Stage1_Map(const Stage1_Map& _Other) = delete;
	Stage1_Map(Stage1_Map&& _Other) noexcept = delete;
	Stage1_Map& operator=(const Stage1_Map& _Other) = delete;
	Stage1_Map& operator=(Stage1_Map&& _Other) noexcept = delete;

protected:

private:

};

