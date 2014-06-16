#include "GameStage.hpp"
#include <iostream>
#include <cmath>

using namespace Insanity;

GameStage::GameStage() : _leftArrow{}, _rightArrow{}, _active{}
{
	_InitBricks();
}
GameStage::~GameStage()
{
}

void GameStage::_InitBricks()
{
	BrickState state;
	state.active = true;

	for (int x = 0; x < 6; x++)
	{
		for (int y = 0; y < 6; y++)
		{
			state.pos[0] = -0.75f + (_brktmpl.GetWidth() * x);
			state.pos[1] = 0.4f + (_brktmpl.GetHeight() * y);
			state.value = 5 * (y + 1);
			_bricks.push_back(state);
		}
	}
}
void GameStage::_HandleInput()
{
	//only if left and right are in different states.
	if (_leftArrow ^ _rightArrow)
	{
		if (_leftArrow) _pad.Move(-0.01f);
		else _pad.Move(0.01f);
	}
	else _pad.Move(0.0f);
}
void GameStage::_ConstrainPaddle()
{
	if (_pad.GetX() < -0.85f) _pad.SetX(-0.85f);
	else if (_pad.GetX() > 0.85f) _pad.SetX(0.85f);
}
void GameStage::_ConstrainBall()
{
	//constrain ball
	float bx = _ball.GetX();
	float by = _ball.GetY();
	if (bx > 0.975)
	{
		_ball.ReflectX();
	}
	else if (bx < -0.975)
	{
		_ball.ReflectX();
	}
	if (by > 0.975)
	{
		_ball.ReflectY();
	}
	else if (by < -0.975)
	{
		Insanity::IApplication::GetInstance()->End();
	}
}
void GameStage::_CollideBallPaddle()
{
	//check for collisions between the ball and other elements.
	Ptr<const TRectangle<float>> ballRect{ _ball.GetRect() };

	//check for collide with paddle
	if (_pad.GetRect()->Intersects(ballRect))
	{
		Ptr<TRectangle<float>> lastBall{ ballRect->Clone() };
		lastBall->SetX(lastBall->GetX() - _ball.GetMotionX());
		if (!_pad.GetRect()->Intersects(lastBall))
		{
			_ball.ReflectX();
		}

		lastBall->SetX(ballRect->GetX());
		lastBall->SetY(lastBall->GetY() - _ball.GetMotionY());
		if (!_pad.GetRect()->Intersects(lastBall))
		{
			_ball.ReflectY();

			float sx = _ball.GetMotionX();
			float sy = _ball.GetMotionY();
			float sl = sqrt((sx * sx) + (sy * sy));

			//impact vector
			float ix = _ball.GetX() - _pad.GetX();
			float iy = _ball.GetY() - _pad.GetY();
			float il = sqrt((ix * ix) + (iy * iy)) / sl;
			ix /= il;
			iy /= il;

			//outbound vector is the ball's motion vector

			float nx = sx + ix;
			float ny = sy + iy;

			float length = sqrt((nx * nx) + (ny * ny)) / sl;
			nx /= length;
			ny /= length;

			_ball.SetMotionX(nx);
			_ball.SetMotionY(ny);
		}
	}
}
void GameStage::_CollideBallBricks()
{
	bool bricksRemain = false;
	bool hasReflectedX = false;
	bool hasReflectedY = false;
	for (BrickState & state : _bricks)
	{
		if (!state.active) continue;

		bricksRemain = true;
		_brktmpl.SetBrickState(&state);
		Ptr<const TRectangle<float>> ballRect{ _ball.GetRect() };
		if (_brktmpl.GetRect()->Intersects(ballRect))
		{
			Ptr<TRectangle<float>> lastBall{ ballRect->Clone() };
			lastBall->SetX(lastBall->GetX() - _ball.GetMotionX());
			if (!_brktmpl.GetRect()->Intersects(lastBall))
			{
				if (!hasReflectedX)
				{
					_ball.ReflectX();
					hasReflectedX = true;
				}
			}

			lastBall->SetX(ballRect->GetX());
			lastBall->SetY(lastBall->GetY() - _ball.GetMotionY());
			if (!_brktmpl.GetRect()->Intersects(lastBall))
			{
				if (!hasReflectedY)
				{
					_ball.ReflectY();
					hasReflectedY = true;
				}
			}

			//one way or another, we did just collide with the current brick.
			state.active = false;
			_score += state.value;
			std::cout << "Score: " << _score << std::endl;
		}
	}

	if (!bricksRemain)
	{
		_active = false;

		_ball.SetX(0.0f);
		_ball.SetY(0.0f);
		if (_ball.GetMotionX() < 0.0f) _ball.ReflectX();
		if (_ball.GetMotionY() > 0.0f) _ball.ReflectY();

		_pad.SetX(0.0f);

		_bricks.clear();
		_InitBricks();
	}
}

void GameStage::Draw(Insanity::IShaderProgram * prog)
{
	_pad.Draw(prog);
	_ball.Draw(prog);
	for (BrickState const& bs : _bricks)
	{
		_brktmpl.SetBrickState(&bs);
		_brktmpl.Draw(prog);
	}
}
void GameStage::Update()
{
	//don't update before activating the game.
	if (!_active) return;

	_HandleInput();

	_pad.Update();
	_ball.Update();

	//ensure the paddle and ball stay within the walls
	_ConstrainPaddle();
	_ConstrainBall();

	_CollideBallPaddle();
	_CollideBallBricks();
}

void GameStage::SetArrowState(Insanity::EKey key, bool state)
{
	if (key == Insanity::EKeyMap::LeftArrow) _leftArrow = state;
	else if (key == Insanity::EKeyMap::RightArrow) _rightArrow = state;
}
void GameStage::SetActive(bool active)
{
	_active = active;
}
void GameStage::ToggleActive()
{
	_active = !_active;
}