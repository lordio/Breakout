#ifndef BREAKOUT_BRICK
#define BREAKOUT_BRICK

#include "Drawable.hpp"
#include <Insanity.hpp>
#include <gel.hpp>
#include <array>

struct BrickState
{
	Insanity::TVector<float, 2> pos;
	Insanity::u64 value;
	bool active;
};

//represents a brick template; applying a BrickState
class Brick : public Drawable
{
	GLuint _arr;
	GLuint _buf;
	std::array<Insanity::u32, 6> _indices;
	Insanity::Ptr<Insanity::TRectangle<float>> _rect;

	//The brick state to use for drawing.
	BrickState const * _instState;
public:
	Brick();
	~Brick();

	void SetBrickState(BrickState const * state);
	void Draw(Insanity::IShaderProgram * prog) override;

	Insanity::TRectangle<float> const * GetRect() const;

	float GetWidth() const;
	float GetHeight() const;
};

#endif