#include "MarioHelper.h"

UWindowImage* MarioHelper::ColMapImage = nullptr;
FVector MarioHelper::Gravity = { 0.f, 1500.0f };
std::map<MarioState, std::string> StateList;


MarioHelper::MarioHelper()
{

}

MarioHelper::~MarioHelper()
{
}