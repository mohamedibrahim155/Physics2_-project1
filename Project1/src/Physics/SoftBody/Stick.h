#pragma once
#include "Point.h"

struct Stick
{
	Stick() {};
	Stick(Point* _pointA, Point* _pointB) : pointA(_pointA), pointB(_pointB)
	{
		restLength = glm::distance(_pointA->position, _pointB->position);

		_pointA->connectedSticks.push_back(this);
		_pointB->connectedSticks.push_back(this);
	};

	Point* pointA = nullptr;
	Point* pointB = nullptr;
	float restLength = 0;
	bool isActive = true;
	bool isLocked = false;
};