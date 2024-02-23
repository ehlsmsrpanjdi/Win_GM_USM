#pragma once
#include "ItemBase.h"

// Ό³Έν :
class MushRoom : public ItemBase
{
public:
	// constrcuter destructer
	MushRoom();
	~MushRoom();

	// delete Function
	MushRoom(const MushRoom& _Other) = delete;
	MushRoom(MushRoom&& _Other) noexcept = delete;
	MushRoom& operator=(const MushRoom& _Other) = delete;
	MushRoom& operator=(MushRoom&& _Other) noexcept = delete;

protected:

	void BeginPlay() override;


private:

};

