#include "PipeCheat.h"
#include "MarioHelper.h"

PipeCheat::PipeCheat() 
{
}

PipeCheat::~PipeCheat() 
{
}

void PipeCheat::BeginPlay()
{
	BodyRenderer = CreateImageRenderer(MarioRenderOrder::Cheat);
	BodyRenderer->SetTransform({ {0,0}, {128, 128} });
	BodyRenderer->SetImage("Pipe.png");
}

