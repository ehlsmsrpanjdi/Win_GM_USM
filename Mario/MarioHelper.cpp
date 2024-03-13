#include "MarioHelper.h"
#include <string>
#include "PlayLevel.h"
#include "LastLevel.h"
#include "Mario.h"
#include "PlayLevel2.h"
#include "PlayLevel3.h"

UWindowImage* MarioHelper::ColMapImage = nullptr;
FVector MarioHelper::Gravity = { 0.f, 1500.0f };
MarioClass MarioHelper::MyMarioClass = MarioClass::Small;
float MarioHelper::MonsterScoreResetTime = 5.f;
bool MarioHelper::SoundOff = false;

bool MarioHelper::Stage1Sound = true;
bool MarioHelper::Stage2Sound = true;

int MarioHelper::MarioTime = 1400;
int MarioHelper::MarioCoinCount = 200;
int MarioHelper::MarioWorldCount = 11;
int MarioHelper::MarioTotalScore = 1000000;
int MarioHelper::MarioLife = 3;
int MarioHelper::MonsterScore = 0;
int MarioHelper::ItemScore = 0;
std::string MarioHelper::PrevLevelName = "Stage1";
bool MarioHelper::LevelEnd = false;
bool MarioHelper::GameEnd = false;

bool MarioHelper::CameraOff = false;

void MarioHelper::SetNextLevel(std::string _LevelName) {
	MarioHelper::NextLevelName = _LevelName;
}

std::string MarioHelper::GetNextLevel() {
	return MarioHelper::NextLevelName;
}

std::string MarioHelper::NextLevelName = "Stage2";


bool MarioHelper::StageOneInit = false;
bool MarioHelper::StageTwoInit = false;
bool MarioHelper::StageThreeInit = false;
bool MarioHelper::LastStageInit = false;

float MarioHelper::CameraX = 0;
float MarioHelper::WindowCenter = 0;

MarioHelper::MarioHelper()
{

}

MarioHelper::~MarioHelper()
{
}

void MarioHelper::CreateLevel(std::string _LevelName)
{
	if (_LevelName == "Stage1") {
		GEngine->CreateLevel<UPlayLevel>("Stage1");
	}
	if (_LevelName == "Stage2") {
		GEngine->CreateLevel<PlayLevel2>("Stage2");
	}
	if (_LevelName == "Stage3") {
		GEngine->CreateLevel<PlayLevel3>("Stage3");
	}
	if (_LevelName == "LastStage") {
		GEngine->CreateLevel<LastLevel>("LastStage");
	}
}

bool MarioHelper::BottomCheck(FVector _NextVector) {
	FVector CurLocation = _NextVector;

	FVector BottomLeft = MarioHelper::GetBottomLeftVector(CurLocation);
	FVector BottomRight = MarioHelper::GetBottomRightVector(CurLocation);

	Color8Bit CheckColor_BottomLeft = MarioHelper::ColMapImage->GetColor(BottomLeft.iX(), BottomLeft.iY(), Color8Bit(0, 0, 0, 0));
	Color8Bit CheckColor_BottomRight = MarioHelper::ColMapImage->GetColor(BottomRight.iX(), BottomRight.iY(), Color8Bit(0, 0, 0, 0));

	bool FirstCondition = (Color8Bit(255, 0, 255, 0) == CheckColor_BottomLeft);
	bool SecondCondition = (Color8Bit(255, 0, 255, 0) == CheckColor_BottomRight);


	if (FirstCondition || SecondCondition) {
		return true;
	}

	return false;
}

bool MarioHelper::RightCheck(FVector _NextVector) {
	FVector CurLocation = _NextVector;

	FVector RightTop = MarioHelper::GetRightTopVector(CurLocation);
	FVector RightBottom = MarioHelper::GetRightBottomVector(CurLocation);

	Color8Bit CheckColor_RightTop = MarioHelper::ColMapImage->GetColor(RightTop.iX(), RightTop.iY(), Color8Bit(0, 0, 0, 0));
	Color8Bit CheckColor_RightBottom = MarioHelper::ColMapImage->GetColor(RightBottom.iX(), RightBottom.iY(), Color8Bit(0, 0, 0, 0));

	bool FirstCondition = (Color8Bit(255, 0, 255, 0) == CheckColor_RightBottom);
	bool SecondCondition = (Color8Bit(255, 0, 255, 0) == CheckColor_RightTop);

	if (FirstCondition || SecondCondition) {
		return true;
	}

	return false;
}

bool MarioHelper::LeftCheck(FVector _NextVector) {
	FVector CurLocation = _NextVector;

	FVector LeftTop = MarioHelper::GetLeftTopVector(CurLocation);
	FVector LeftBottom = MarioHelper::GetLeftBottomVector(CurLocation);

	Color8Bit CheckColor_LeftTop = MarioHelper::ColMapImage->GetColor(LeftTop.iX(), LeftTop.iY(), Color8Bit(0, 0, 0, 0));
	Color8Bit CheckColor_LeftBottom = MarioHelper::ColMapImage->GetColor(LeftBottom.iX(), LeftBottom.iY(), Color8Bit(0, 0, 0, 0));

	bool FirstCondition = (Color8Bit(255, 0, 255, 0) == CheckColor_LeftBottom);
	bool SecondCondition = (Color8Bit(255, 0, 255, 0) == CheckColor_LeftTop);


	if (FirstCondition || SecondCondition) {
		return true;
	}

	return false;
}

void MarioHelper::AddMonsterScore(int _Score)
{
	MarioHelper::MonsterScore += _Score;
	MarioHelper::MonsterScoreResetTime = 2.0f;
}

void MarioHelper::SetItemScore(int _Score) {
	MarioHelper::ItemScore = _Score;
}

FVector MarioHelper::GetBottomLeftVector(FVector _NextVector) {

	FVector CurLocation = _NextVector;
	int EdgeLocation_Left = static_cast<int>(CurLocation.iX() - 24);
	int EdgeLocation_Bottom = static_cast<int>(CurLocation.iY());

	return FVector{ EdgeLocation_Left , EdgeLocation_Bottom };
}

FVector MarioHelper::GetBottomRightVector(FVector _NextVector) {

	FVector CurLocation = _NextVector;
	int EdgeLocation_Right = static_cast<int>(CurLocation.iX() + 24);
	int EdgeLocation_Bottom = static_cast<int>(CurLocation.iY());

	return FVector{ EdgeLocation_Right , EdgeLocation_Bottom };
}

FVector MarioHelper::GetLeftTopVector(FVector _NextVector) {
	FVector CurLocation = _NextVector;
	int EdgeLocation_Left = static_cast<int>(CurLocation.X - 32.f);
	int EdgeLocation_Top = static_cast<int>(CurLocation.Y - 32.f);

	return FVector{ EdgeLocation_Left , EdgeLocation_Top };
}

FVector MarioHelper::GetLeftBottomVector(FVector _NextVector) {
	FVector CurLocation = _NextVector;
	int EdgeLocation_Left = static_cast<int>(CurLocation.X - 32.f);
	int EdgeLocation_Bottom = static_cast<int>(CurLocation.Y - 3.f);

	return FVector{ EdgeLocation_Left , EdgeLocation_Bottom };
}


FVector MarioHelper::GetRightTopVector(FVector _NextVector) {
	FVector CurLocation = _NextVector;
	int EdgeLocation_Right = static_cast<int>(CurLocation.X + 32.f);
	int EdgeLocation_Top = static_cast<int>(CurLocation.Y - 32.f);

	return FVector{ EdgeLocation_Right , EdgeLocation_Top };
}

FVector MarioHelper::GetRightBottomVector(FVector _NextVector) {
	FVector CurLocation = _NextVector;
	int EdgeLocation_Right = static_cast<int>(CurLocation.X + 32.f);
	int EdgeLocation_Bottom = static_cast<int>(CurLocation.Y - 3.f);

	return FVector{ EdgeLocation_Right , EdgeLocation_Bottom };
}

//std::string_view MarioHelper::ReturnString(int _Value)
//{
//	std::string_view str = std::to_string(_Value);
//	return str;
//}

void MarioHelper::MarioTimeReset()
{
	MarioHelper::MarioTime = 1400;
}

void MarioHelper::MarioCoinReset()
{
	MarioHelper::MarioCoinCount = 100;
}

void MarioHelper::SetPrevLevel(std::string _LevelName)
{
	MarioHelper::PrevLevelName = _LevelName;
}

void MarioHelper::MarioWorldSet()
{
	if (MarioHelper::NextLevelName._Equal("LastStage")) {
		MarioHelper::MarioWorldCount = 14;
	}
	else if (MarioHelper::NextLevelName._Equal("Stage3")) {
		MarioHelper::MarioWorldCount = 13;
	}
	else if (MarioHelper::NextLevelName._Equal("Stage2")) {
		MarioHelper::MarioWorldCount = 12;
	}
	else if (MarioHelper::NextLevelName._Equal("Stage1")) {
		MarioHelper::MarioWorldCount = 11;
	}
	return;
}

std::string MarioHelper::GetPrevLevel()
{
	return MarioHelper::PrevLevelName;
}
