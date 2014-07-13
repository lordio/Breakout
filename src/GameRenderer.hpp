#ifndef BREAKOUT_GAME_RENDERER
#define BREAKOUT_GAME_RENDERER

#include <Insanity.hpp>
#include <Default.hpp>

#include <array>
#include <list>

class GameWindow;
class Paddle;
class Drawable;

class GameRenderer : public Insanity::Default::Renderer
{
	std::array<float, 4> _clearColor;
	std::list<Drawable*> _drawList;
public:
	GameRenderer(GameWindow * win, Insanity::IConfigObject const * cfg);
	~GameRenderer();
	void Add(Drawable * draw);

	void Render() override;
};

#endif