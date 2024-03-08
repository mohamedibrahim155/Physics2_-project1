#pragma once
#include "BaseMyThread.h"
#include <iostream>
class ExampleClassTwo : public BaseMyThread
{
public:
	ExampleClassTwo();
	~ExampleClassTwo();


	// Inherited via BaseMyThread
	void ThreadUpdate(float deltaTime) override;
};

