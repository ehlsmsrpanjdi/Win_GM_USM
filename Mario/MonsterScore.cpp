#include "MonsterScore.h"
#include "MarioHelper.h"

MonsterScore::MonsterScore() 
{
}

MonsterScore::~MonsterScore() 
{
}

void MonsterScore::BeginPlay()
{
	AActor::BeginPlay();

	std::string Index = std::to_string(MarioHelper::MonsterScore);
	std::string str;
	for (int i = 0; i < Index.length(); ++i) {
		str = Index.substr(i, 1);
		str.append(".png");
		ScoreRenderer[i] = CreateImageRenderer(static_cast<int>(MarioRenderOrder::UI));
		ScoreRenderer[i]->SetImage(str);
		ScoreRenderer[i]->SetTransform({ { static_cast<int>(Index.length() * -8) + i * 16,-64 }, {16,16} });
	}
	MarioHelper::MarioTotalScore += MarioHelper::MonsterScore;
	Destroy(2.0f);
}

void MonsterScore::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	AddActorLocation(FVector::Up * _DeltaTime * 10);
}

