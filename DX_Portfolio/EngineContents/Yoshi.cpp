#include "PreCompile.h"
#include "Yoshi.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/DefaultSceneComponent.h>

AYoshi::AYoshi()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	UEngineSprite::CreateSpriteToMeta("YoshiAndMario.png", ".sdata");
	YoshiRenderer = CreateDefaultSubObject<USpriteRenderer>();
	YoshiRenderer->SetupAttachment(RootComponent);
	YoshiRenderer->SetAutoScaleRatio(3.0f);
	YoshiRenderer->SetRelativeLocation({ 0, 0, -10 });

	YoshiRenderer->CreateAnimation("Idle", "YoshiAndMario.png", { 7, 8, 9, 10, 11, 10, 9, 8, 7, 8, 9, 10, 11, 10, 9, 8, 7, 8, 9, 10, 11, 10, 9, 8, 7, 8, 9, 10, 11, 10, 9, 8 }, 0.15f);
	YoshiRenderer->CreateAnimation("Move", "YoshiAndMario.png", 40, 50, 0.08f);
	YoshiRenderer->ChangeAnimation("Idle");

	State = EPlayerState::IDLE;
}

AYoshi::~AYoshi()
{
}



void AYoshi::BeginPlay()
{
	AActor::BeginPlay();
}

void AYoshi::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	PlayerFSM(_DeltaTime);

	UEngineDebug::OutPutString(std::to_string(Color.R) + "," + std::to_string(Color.G) + "," + std::to_string(Color.B));
}

void AYoshi::SetCheckPos()
{
	CheckPos = GetActorLocation();

	switch (Dir)
	{
	case EDirection::LEFT:
		CheckPos.X += -Speed;
		CheckPos.Y = -CheckPos.Y;
		break;
	case EDirection::RIGHT:
		CheckPos.X += Speed;
		CheckPos.Y = -CheckPos.Y;
		break;
	case EDirection::UP:
		CheckPos.Y += Speed;
		CheckPos.Y = -CheckPos.Y;
		break;
	case EDirection::DOWN:
		CheckPos.Y -= Speed;
		CheckPos.Y = -CheckPos.Y;
		break;
	}
}

void AYoshi::PlayerFSM(float _DeltaTime)
{
	switch (State)
	{
	case EPlayerState::IDLE:
		IdleStart(_DeltaTime);
		break;
	case EPlayerState::MOVE:
		MoveStart(_DeltaTime);
		break;
	case EPlayerState::MAX:
		break;
	}
}

void AYoshi::IdleStart(float _DeltaTime)
{
	Dir = EDirection::MAX;
	YoshiRenderer->ChangeAnimation("Idle");

	Idle(_DeltaTime);
}

void AYoshi::Idle(float _DeltaTime)
{
	if (true == UEngineInput::IsPress(VK_LEFT) || true == UEngineInput::IsPress(VK_RIGHT)
		|| true == UEngineInput::IsPress(VK_UP) || true == UEngineInput::IsPress(VK_DOWN))
	{
		State = EPlayerState::MOVE;
		return;
	}
}

void AYoshi::MoveStart(float _DeltaTime)
{
	YoshiRenderer->ChangeAnimation("Move");
	Move(_DeltaTime);
}

void AYoshi::Move(float _DeltaTime)
{
	if (true == UEngineInput::IsPress(VK_RIGHT))
	{
		Dir = EDirection::RIGHT;
		SetCheckPos();
		if (false == Color.operator==(UColor{ 255, 0, 255, 255 }))
		{
			AddActorLocation({ Speed, 0.0f, 0.0f });
			YoshiRenderer->SetRotation({ 0.0f, 0.0f, 0.0f });
		}
	}

	if (true == UEngineInput::IsPress(VK_LEFT))
	{
		Dir = EDirection::LEFT;
		SetCheckPos();
		if (false == Color.operator==(UColor{ 255, 0, 255, 255 }))
		{
			AddActorLocation({ -Speed, 0.0f, 0.0f });
			YoshiRenderer->SetRotation({ 0.0f, 0.0f, 0.0f });
		}
	}

	if (true == UEngineInput::IsPress(VK_DOWN))
	{
		Dir = EDirection::DOWN;
		SetCheckPos();
		if (false == Color.operator==(UColor{ 255, 0, 255, 255 }))
		{
			AddActorLocation({ 0, -Speed, 0 });
		}
	}

	if (true == UEngineInput::IsPress(VK_UP))
	{
		Dir = EDirection::UP;
		SetCheckPos();
		if (false == Color.operator==(UColor{ 255, 0, 255, 255 }))
		{
			AddActorLocation({ 0, Speed, 0 });
		}
	}

	if (false == UEngineInput::IsPress(VK_LEFT) && false == UEngineInput::IsPress(VK_RIGHT)
		&& false == UEngineInput::IsPress(VK_UP) && false == UEngineInput::IsPress(VK_DOWN))
	{
		State = EPlayerState::IDLE;
		return;
	}
}

