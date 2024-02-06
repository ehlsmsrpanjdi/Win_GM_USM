#pragma once
#include <iostream>
// Ό³Έν :
class MarioLevelBase
{
public:
	// constrcuter destructer
	MarioLevelBase();
	~MarioLevelBase();

	// delete Function
	MarioLevelBase(const MarioLevelBase& _Other) = delete;
	MarioLevelBase(MarioLevelBase&& _Other) noexcept = delete;
	MarioLevelBase& operator=(const MarioLevelBase& _Other) = delete;
	MarioLevelBase& operator=(MarioLevelBase&& _Other) noexcept = delete;

protected:

private:
	std::string LevelName;
};

