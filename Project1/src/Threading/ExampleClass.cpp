#include "ExampleClass.h"
#include "ThreadManager.h"
#include "../GraphicsRender.h"


ExampleClass::ExampleClass()
{
	LoadModel("Models/Plant.fbm/Plant.fbx");
	//LoadModel("../../Models/Plant.fbm/Plant.fbx");
	GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().defaultShader);

	ThreadManager::Getinstance().AddThread(this);
}

ExampleClass::~ExampleClass()
{
}

void ExampleClass::ThreadUpdate(float deltaTime)
{
	//std::cout << "Inside Example Class Update" << std::endl;
}

void ExampleClass::Update(float deltaTime)
{
	//std::cout << "inside entity update" << std::endl;
	transform.position.x += 0.1f * deltaTime;
	ThreadUpdate(deltaTime);
}
