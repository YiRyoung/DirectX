#include "PreCompile.h"
#include "Stage100GameMode.h"
#include "Stage100.h"
#include "Yoshi.h"

#include <EngineBase/EngineDebug.h>

#include <EnginePlatform/EngineInput.h>
#include <EnginePlatform/EngineWinImage.h>

#include <EngineCore/Level.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/EngineCamera.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>

class DebugTool : public UEngineGUIWindow
{
public:
	void OnGUI() override
	{
		if (true == ImGui::Button("FreeCameraOn"))
		{
			GetWorld()->GetMainCamera()->FreeCameraSwitch();
		}
	}
};

AStage100GameMode::AStage100GameMode()
{
	
	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -560.0f, 1.0f });
	Camera->GetCameraComponent()->SetZSort(0, true);

}

AStage100GameMode::~AStage100GameMode()
{
}

void AStage100GameMode::BeginPlay()
{
	AActor::BeginPlay();

	Stage = GetWorld()->SpawnActor<AStage100>();
	Stage->SetBackground();
	Stage->SetActorLocation({ 4608 * 0.5f, 3072 * -0.5f });

	GetWorld()->GetMainPawn()->SetActorLocation({ 420.0f, -2687.0f, 0.0f });
	dynamic_cast<AYoshi*>(GetWorld()->GetMainPawn())->SetCamera(GetWorld()->GetMainCamera());
	Stage->SwitchColStage(false);
}

void AStage100GameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	SetCameraBoundary();

	if (true == UEngineInput::IsDown('V'))
	{
		bool IsTrue = (Stage->GetColStageOn());
		Stage->SwitchColStage(!IsTrue);
	}
}

void AStage100GameMode::LevelChangeStart()
{
	AActor::LevelChangeStart();

	{
		std::shared_ptr<DebugTool> Window = UEngineGUI::FindGUIWindow<DebugTool>("DebugTool");

		if (nullptr == Window)
		{
			Window = UEngineGUI::CreateGUIWindow<DebugTool>("DebugTool");
		}

		Window->SetActive(true);
	}
}

void AStage100GameMode::LevelChangeEnd()
{
	AActor::LevelChangeEnd();
}

void AStage100GameMode::SetCameraBoundary()
{
	Camera->SetActorLocation({ GetWorld()->GetMainPawn()->GetActorLocation().X, GetWorld()->GetMainPawn()->GetActorLocation().Y, -520.0f});
	
	FVector ResultCameraPos = { 0.0f, 0.0f, 0.0f };
	FVector ScreenSize = UEngineCore::GetScreenScale();
	FVector MapSize = Stage->GetMapScale();
	FVector CameraPos = Camera->GetActorLocation();

	if ((ScreenSize.X * 0.5f) >= CameraPos.X)
	{
		ResultCameraPos.X = ScreenSize.X * 0.5f;
	}
	else if (MapSize.X - (ScreenSize.X * 0.5f) <= CameraPos.X)
	{
		ResultCameraPos.X = MapSize.X - (ScreenSize.X * 0.5f);
	}
	else
	{
		ResultCameraPos.X = GetWorld()->GetMainPawn()->GetActorLocation().X;
	}

	if ((ScreenSize.Y * -0.5f) <= CameraPos.Y)
	{
		ResultCameraPos.Y = (ScreenSize.Y * -0.5f);
	}
	else if ((-MapSize.Y + (ScreenSize.Y * 0.5f)) >= CameraPos.Y)
	{
		ResultCameraPos.Y = (-MapSize.Y + (ScreenSize.Y * 0.5f));
	}
	else
	{
		ResultCameraPos.Y = GetWorld()->GetMainPawn()->GetActorLocation().Y;
	}

	Camera->SetActorLocation({ ResultCameraPos.X, ResultCameraPos.Y + 100.0f, -520.0f });
}