#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>
#include <EngineCore\ImageRenderer.h>
#include <map>


enum MarioRenderOrder
{
	Map,
	Block,
	Monster,
	Player,
};

enum class EActorDir
{
	Left = -1,
	None = 0,
	Right = 1,
};

enum class MarioState
{
	None,
	Idle,
	Move,
	Jump,
	DirChange,
	Interactive,
	Dead,
};

enum class MonsterState {
	None,
	Idle,
	Crouch,
	Dead,
	CrouchMove,
	Critical,
};

enum class BlockState {
	Item,
	None,

};

enum class MarioCollisionOrder
{
	PlayerBullet,
	Monster,
	Block,
	Player,

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

