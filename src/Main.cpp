#include <Insanity.hpp>
#include <Default.hpp>
using namespace Insanity;
using namespace Insanity::Default;

#include "GameWindow.hpp"
#include "GameRenderer.hpp"
#include "GameStage.hpp"

#include <chrono>

int main(int argc, char const * argv [])
{
	Ptr<IApplication> app{ IApplication::GetInstance() };

	Ptr<IConfigFile> cf{ IConfigFile::GetInstance("../../../bin/Win32/Debug/Breakout.cfg") };
	if (!cf->IsValid()) return 1;

	Ptr<GameWindow> win{ new GameWindow{ cf } };
	Ptr<GameRenderer> rend{ win->GetRenderer() };

	GameStage stage;
	win->SetStage(&stage);
	rend->Add(&stage);

	while (app->Update())
	{
		stage.Update();

		rend->Render();
		rend->Present();
	}

	return 0;
}