#ifndef BREAKOUT_DRAWABLE
#define BREAKOUT_DRAWABLE

class Drawable
{
public:
	virtual ~Drawable() {}
	virtual void Draw() = 0;
};

#endif