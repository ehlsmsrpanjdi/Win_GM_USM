#include "MarioHelper.h"

UWindowImage* MarioHelper::ColMapImage = nullptr;
float MarioHelper::Gravity = 500.0f;
std::map<EPlayState, std::string> StateList;


MarioHelper::MarioHelper()
{

}

MarioHelper::~MarioHelper()
{
}

