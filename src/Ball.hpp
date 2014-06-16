#ifndef BREAKOUT_BALL
#define BREAKOUT_BALL

#include "Drawable.hpp"
#include "Updatable.hpp"

#include <Insanity.hpp>
#include <gel.hpp>

#include <array>

class Ball : public Drawable, public Updatable
{
	GLuint _arr;
	GLuint _buf;
	std::array<Insanity::u32, 6> _indices;
	Insanity::TVector<float, 2> _pos;
	Insanity::TVector<float, 2> _motion;
	Insanity::Ptr<Insanity::TRectangle<float>> _rect;
public:
	Ball();
	~Ball();

	void Draw(Insanity::IShaderProgram * prog) override;
	void Update() override;

	float GetX() const;
	float GetY() const;

	void SetX(float x);
	void SetY(float y);

	float GetMotionX() const;
	float GetMotionY() const;
	void SetMotionX(float x);
	void SetMotionY(float y);

	void ReflectX();
	void ReflectY();

	Insanity::TRectangle<float> const * GetRect() const;
};

#endif