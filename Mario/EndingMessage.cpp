#include "EndingMessage.h"
#include "MarioHelper.h"

EndingMessage::EndingMessage() 
{
}

EndingMessage::~EndingMessage() 
{
}

void EndingMessage::BeginPlay()
{
	EndingMessageBox = CreateImageRenderer(MarioRenderOrder::UI);
	EndingMessageBox->SetImage("EndingMessage.png");
	EndingMessageBox->SetTransform({ { 0,0 },{768,320} });
	
}

void EndingMessage::Tick(float _DeltaTime)
{
}

