#pragma once
#include "BaseMyThread.h"
#include <iostream>
#include "../model.h"
class ExampleClass : public BaseMyThread, public Model
{
public:
	ExampleClass();
	~ExampleClass();


	// Inherited via BaseMyThread
	void ThreadUpdate(float deltaTime) override;
	void Update(float deltaTime) override;
};

