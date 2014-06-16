#ifndef BREAKOUT_GAME_STAGE
#define BREAKOUT_GAME_STAGE

//Game state manager class.
//	Handles collision detection on Update.

#include "Paddle.hpp"
#include "Ball.hpp"
#include "Brick.hpp"

#include <Insanity.hpp>

#include <list>

class GameStage : public Drawable, public Updatable
{
	bool _leftArrow;
	bool _rightArrow;
	bool _active;

	Paddle _pad;
	Ball _ball;
	
	Brick _brktmpl;
	std::list<BrickState> _bricks;

	Insanity::u64 _score;

	void _InitBricks();
	void _HandleInput();
	void _ConstrainPaddle();
	void _ConstrainBall();
	void _CollideBallPaddle();
	void _CollideBallBricks();
public:
	GameStage();
	~GameStage();

	void Draw(Insanity::IShaderProgram * prog) override;
	void Update() override;

	void SetArrowState(Insanity::EKey key, bool state);
	void SetActive(bool active);
	void ToggleActive();
};

#endif