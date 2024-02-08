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
	Left,
	Right,
};

enum class EPlayState
{
	None,
	Idle,
	Move,
	Jump,
};





// Ό³Έν :
class MarioHelper
{
public:
	static UWindowImage* ColMapImage;
	static float Gravity;
	static std::map<EPlayState, std::string> StateList;
private:
	// constrcuter destructer
	MarioHelper();
	~MarioHelper();
};

