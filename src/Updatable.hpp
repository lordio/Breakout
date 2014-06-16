#ifndef BREAKOUT_UPDATABLE
#define BREAKOUT_UPDATABLE

class Updatable
{
public:
	virtual ~Updatable() {}
	virtual void Update() = 0;
};


#endif