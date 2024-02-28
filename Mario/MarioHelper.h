#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>
#include <EngineCore\ImageRenderer.h>
#include <map>
#include "MarioUI.h"


enum MarioRenderOrder{
	Map,
	Monster,
	Player,
	Item,
	Block,
	Fire,
	UI,
};

enum class EActorDir{
	Left = -1,
	None = 0,
	Right = 1,
};

enum class MarioState{
	None,
	Idle,
	Move,
	Jump,
	DirChange,
	Interactive,
	Dead,
	End,
	EndMove,
	Changing,
};

enum class MarioClass {
	Small,
	Big,
	Fire,
};

enum class MonsterState {
	None,
	Idle,
	Crouch,
	CrouchMove,
	Dead,
	Excute,
};

enum class BlockState {
	None,
	ItemBlock,
	Brick,
	ItemBrick,
	Interactive,
	Default,
};

enum class ItemState {
	None,
	Spawn,
	MushRoom,
	Flower,
	Star,
	Coin,
};

enum class MarioCollisionOrder{
	Map,
	Monster,
	Player,
	Item,
	Block,
	Fire,
};



// Ό³Έν :
class MarioHelper{
public:
	static UWindowImage* ColMapImage;
	static FVector Gravity;

	static int MarioTime;
	static int MarioCoinCount;
	static int MarioTotalScore;
	static int MarioLife;

	static bool BottomCheck(FVector _NextVector);
	static bool LeftCheck(FVector _NextVector);
	static bool RightCheck(FVector _NextVector);

	static FVector GetBottomLeftVector(FVector _NextVector);
	static FVector GetBottomRightVector(FVector _NextVector);
	static FVector GetLeftTopVector(FVector _NextVector);
	static FVector GetLeftBottomVector(FVector _NextVector);
	static FVector GetRightTopVector(FVector _NextVector);
	static FVector GetRightBottomVector(FVector _NextVector);

	static std::string_view ReturnString(int _Value);

	static void MarioTimeReset();

private:
	// constrcuter destructer
	MarioHelper();
	~MarioHelper();
};

