#include "ExampleClassTwo.h"
#include "ThreadManager.h"
ExampleClassTwo::ExampleClassTwo()
{
	ThreadManager::Getinstance().AddThread(this);
}

ExampleClassTwo::~ExampleClassTwo()
{
}

void ExampleClassTwo::ThreadUpdate(float deltaTime)
{
	std::cout << "Inside Example Class Two Update" << std::endl;
}
