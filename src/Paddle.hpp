#ifndef BREAKOUT_PADDLE
#define BREAKOUT_PADDLE

#include "Drawable.hpp"
#include "Updatable.hpp"
#include <gel.hpp>
#include <Insanity.hpp>
#include <array>

class Paddle : public Drawable, public Updatable
{
	GLuint _arr;
	GLuint _buf;
	std::array<Insanity::u32, 6> _indices;
	Insanity::TVector<float, 2> _pos;
	float _motion;
	Insanity::Ptr<Insanity::TRectangle<float>> _rect;
public:
	Paddle();
	~Paddle();

	void Draw(Insanity::IShaderProgram * prog) override;
	void Update() override;

	void Move(float x);

	float GetX() const;
	void SetX(float x);

	float GetY() const;

	Insanity::TRectangle<float> const * GetRect() const;
};

#endif