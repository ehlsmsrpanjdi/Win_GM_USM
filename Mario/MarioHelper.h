#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>
#include <EngineCore\ImageRenderer.h>
#include <map>


enum MarioRenderOrder
{
	Map,
	Monster,
	Player,
	Item,
	Block,
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
	Excute,
	Critical,
};

enum class BlockState {
	Item,
	Brick,
	None,
	Break,
	Interactive,
};

enum class MarioCollisionOrder
{
	Map,
	Monster,
	Player,
	Item,
	Block,
};



// Ό³Έν :
class MarioHelper
{
public:
	static UWindowImage* ColMapImage;
	static FVector Gravity;
	static std::map<MarioState, std::string> StateList;

	static bool BottomCheck(FVector _NextVector);
	static bool LeftCheck(FVector _NextVector);
	static bool RightCheck(FVector _NextVector);

	static FVector GetBottomLeftVector(FVector _NextVector);
	static FVector GetBottomRightVector(FVector _NextVector);
	static FVector GetLeftTopVector(FVector _NextVector);
	static FVector GetLeftBottomVector(FVector _NextVector);
	static FVector GetRightTopVector(FVector _NextVector);
	static FVector GetRightBottomVector(FVector _NextVector);


private:
	// constrcuter destructer
	MarioHelper();
	~MarioHelper();
};

