#pragma once
#include <EngineCore/GameMode.h>
// ���� :
class AStage101GameMode : public AGameMode
{
public:
	// constrcuter destructer
	AStage101GameMode();
	~AStage101GameMode();

	// delete Function
	AStage101GameMode(const AStage101GameMode& _Other) = delete;
	AStage101GameMode(AStage101GameMode&& _Other) noexcept = delete;
	AStage101GameMode& operator=(const AStage101GameMode& _Other) = delete;
	AStage101GameMode& operator=(AStage101GameMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class AStage101> Stage;
};

