#pragma once
#include <EngineCore/Actor.h>
// Ό³Έν :
class MonsterScore : public AActor
{
public:
	// constrcuter destructer
	MonsterScore();
	~MonsterScore();

	// delete Function
	MonsterScore(const MonsterScore& _Other) = delete;
	MonsterScore(MonsterScore&& _Other) noexcept = delete;
	MonsterScore& operator=(const MonsterScore& _Other) = delete;
	MonsterScore& operator=(MonsterScore&& _Other) noexcept = delete;

protected:
	UImageRenderer* ScoreRenderer[5] = { nullptr, };

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	//ScoreRendererLocation += {0.f, -0.1f};
	//ScoreRenderer->SetTransform({ ScoreRendererLocation, {60,20} });
	
	//ScoreRenderer = CreateImageRenderer(MarioRenderOrder::UI);
	//FVector OwnerLocation = this->GetActorLocation();
	//ScoreRenderer->SetImage("100.png");
	//ScoreRenderer->SetTransform({ {0,-20}, {60,20} });
	//ScoreRendererLocation = ScoreRenderer->GetTransform().GetPosition();
	//MarioHelper::MarioTotalScore += 100;
};

