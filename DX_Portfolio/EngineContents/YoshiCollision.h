#pragma once

#include "ContentsEnum.h"
// ���� :
class YoshiCollision
{
public:
	// constrcuter destructer
	YoshiCollision();
	YoshiCollision(class AYoshi* _Yoshi);
	~YoshiCollision();

	// delete Function
	YoshiCollision(const YoshiCollision& _Other) = delete;
	YoshiCollision(YoshiCollision&& _Other) noexcept = delete;
	YoshiCollision& operator=(const YoshiCollision& _Other) = delete;
	YoshiCollision& operator=(YoshiCollision&& _Other) noexcept = delete;

	//Warpping Functions
	FVector GetYoshiLocation();
	FVector GetYoshiScale();
	UColor GetColor(FVector _Pos);

	bool CheckPointColor(ECheckDir _Dir, UColor _Color);
	bool CheckLineColor(ECheckDir _Dir, UColor _Color);

	bool IsHill();
	void GroundUp(float _DeltaTime);

protected:

private:
	class AYoshi* Yoshi;
};

