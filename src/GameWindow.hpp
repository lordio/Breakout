#ifndef BREAKOUT_GAME_WINDOW
#define BREAKOUT_GAME_WINDOW

#include <Insanity.hpp>
#include <Default.hpp>

#include "Paddle.hpp"

class GameRenderer;
class GameStage;

class GameWindow : public Insanity::Default::Window
{
	Insanity::Ptr<GameRenderer> _rend;
	Paddle * _pad;
	GameStage * _stage;
public:
	GameWindow(Insanity::IConfigFile const * cf);

	GameRenderer * GetRenderer() const;
	void SetStage(GameStage * stage);

	void MouseHandler(Insanity::EMouseButton button, Insanity::EMouseButtonState state, Insanity::u16 x, Insanity::u16 y) override;
	void ResizeHandler(Insanity::u16 width, Insanity::u16 height) override;
	void KeyHandler(Insanity::EKey key, Insanity::EKeyState state) override;
	void CloseHandler() override;
};

#endif