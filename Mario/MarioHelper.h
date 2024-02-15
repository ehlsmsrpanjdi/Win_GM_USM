#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>
#include <EngineCore\ImageRenderer.h>
#include <map>


enum MarioRenderOrder
{
	Map,
	Monster,
	Player
};

enum class EActorDir
{
	Left = -1,
	Right = 1,
};

enum class MarioState
{
	None,
	Idle,
	Move,
	Jump,
	NotMove,
	DirChange,
};


enum class MarioCollisionOrder
{
	PlayerBullet,
	Monster,
	Player
};



// Ό³Έν :
class MarioHelper
{
public:
	static UWindowImage* ColMapImage;
	static FVector Gravity;
	static std::map<MarioState, std::string> StateList;
private:
	// constrcuter destructer
	MarioHelper();
	~MarioHelper();
};

