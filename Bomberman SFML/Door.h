#pragma once
#include "UnmoveableObject.h"

class Door : public UnmoveableObject
{
public:
	Door(); //door constructor
	void clear(); //clears the door, new position will be (0,0)
};

