#pragma once
#include <EngineCore/GameMode.h>

class ATitle : public AGameMode
{
public:
	// constrcuter destructer
	ATitle();
	~ATitle();

	// delete Function
	ATitle(const ATitle& _Other) = delete;
	ATitle(ATitle&& _Other) noexcept = delete;
	ATitle& operator=(const ATitle& _Other) = delete;
	ATitle& operator=(ATitle&& _Other) noexcept = delete;

	std::shared_ptr<class USpriteRenderer> GetBackgroundRenderer() const
	{
		return BackgroundRenderer;
	}

	bool IsEnd() const
	{
		return (EndAnimIndex != -1) ? true : false;
	}

	void SetEndAnimIndex(int _StartIndex)
	{
		EndAnimIndex = _StartIndex;
	}

	void EndAnimation();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> BackgroundRenderer;
	std::shared_ptr<class USpriteRenderer> LogoRenderer;

	int EndAnimIndex = -1;
};

