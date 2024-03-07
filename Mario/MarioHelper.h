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
	Cheat,
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
	Crouch,
	CrouchJump,
	Dead,
	End,
	EndMove,
	Changing,
	TelePorting,
	TelePortEnd,
	EndingMove,
	Ending,
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
	Object,
};


// Ό³Έν :
class MarioHelper{
public:
	static UWindowImage* ColMapImage;
	static FVector Gravity;

	static int MarioTime;
	static int MarioCoinCount;
	static int MarioWorldCount;
	static int MarioTotalScore;
	static int MarioLife;
	static bool CameraOff;
	static bool GameEnd;
	static MarioClass MyMarioClass;
	static int MonsterScore;
	static float MonsterScoreResetTime;
	static void AddMonsterScore(int _Score);


	static bool BottomCheck(FVector _NextVector);
	static bool LeftCheck(FVector _NextVector);
	static bool RightCheck(FVector _NextVector);
	static bool LevelEnd;

	static FVector GetBottomLeftVector(FVector _NextVector);
	static FVector GetBottomRightVector(FVector _NextVector);
	static FVector GetLeftTopVector(FVector _NextVector);
	static FVector GetLeftBottomVector(FVector _NextVector);
	static FVector GetRightTopVector(FVector _NextVector);
	static FVector GetRightBottomVector(FVector _NextVector);

	static void SetPrevLevel(std::string _LevelName);
	static std::string GetPrevLevel();
	static std::string PrevLevelName;

	static void SetNextLevel(std::string _LevelName);
	static std::string GetNextLevel();
	static std::string NextLevelName;

	static void MarioTimeReset();
	static void MarioCoinReset();
	static void MarioWorldSet();

	static void CreateLevel(std::string _LevelName);

	static bool StageOneInit;
	static bool LastStageInit;

private:
	// constrcuter destructer
	MarioHelper();
	~MarioHelper();
};

