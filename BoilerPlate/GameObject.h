#pragma once
#ifndef _GameObject_
#define _GameObject_
#include "SDL.h"
class GameObject {

public:
	virtual void Update(double  deltaTime) = 0;
	virtual void Render(int mode) = 0;
	virtual void Clean() = 0;
protected:
	GameObject() {}
	virtual ~GameObject() {};
};
#endif // !_GameObject_
