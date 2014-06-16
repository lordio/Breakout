#include "GameWindow.hpp"
#include "GameRenderer.hpp"

#include "GameStage.hpp"

GameWindow::GameWindow(Insanity::IConfigFile const * cf) : Window{ cf->GetObject("gameWin") }, _rend{ new GameRenderer{ this, cf->GetObject("gameRend") } }
{
}

GameRenderer * GameWindow::GetRenderer() const
{
	return _rend;
}

void GameWindow::SetStage(GameStage * stage)
{
	_stage = stage;
}

void GameWindow::MouseHandler(Insanity::EMouseButton button, Insanity::EMouseButtonState state, Insanity::u16 x, Insanity::u16 y)
{
	if (button == Insanity::EMouseButton::Left && state == Insanity::EMouseButtonState::Up) _stage->SetActive(true);
}

void GameWindow::ResizeHandler(Insanity::u16 width, Insanity::u16 height)
{
	_rend->Resize(width, height);
}	

void GameWindow::KeyHandler(Insanity::EKey key, Insanity::EKeyState state)
{
	if (key == Insanity::EKeyMap::LeftArrow || key == Insanity::EKeyMap::RightArrow) _stage->SetArrowState(key, state == Insanity::EKeyState::Down);
	if (key == Insanity::EKeyMap::Escape && state == Insanity::EKeyState::Down) Close();
	if (key == Insanity::EKeyMap::P && state == Insanity::EKeyState::Down) _stage->ToggleActive();
}

void GameWindow::CloseHandler()
{
	Insanity::IApplication::GetInstance()->End();

	Window::CloseHandler();
}