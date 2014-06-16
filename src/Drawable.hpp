#ifndef BREAKOUT_DRAWABLE
#define BREAKOUT_DRAWABLE

namespace Insanity
{
	class IShaderProgram;
}

class Drawable
{
public:
	virtual ~Drawable() {}
	virtual void Draw(Insanity::IShaderProgram * prog) = 0;
};

#endif