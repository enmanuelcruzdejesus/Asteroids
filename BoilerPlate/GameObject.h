#pragma once
#ifndef _GameObject_
#define _GameObject_
#include "SDL.h"
class GameObject {

public:
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void clean() = 0;
protected:
	GameObject() {}
	virtual ~GameObject() {};
};
#endif // !_GameObject_
