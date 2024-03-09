#pragma once
#include "ThreadStruct.h"

extern ApplicationThread* applicationThreadExtern = new ApplicationThread();


DWORD WINAPI UpdateApplicationThread(LPVOID lpParameter)
{

	ApplicationThread* threadPointer = (ApplicationThread*)lpParameter;

	double lastFrameTime = glfwGetTime();
	double timeStep = 0.0;
	DWORD sleepTime_ms = 1;

	InitializeCriticalSection(&threadPointer->cs);

	while (threadPointer->isActive)
	{
		if (threadPointer->isThreadActive)
		{
			double currentTime = glfwGetTime();
			double deltaTime = currentTime - lastFrameTime;
			lastFrameTime = currentTime;

			timeStep += deltaTime;



			
				//threadPointer->manager->Update(deltaTime);
				//threadPointer->entityManager->Update(deltaTime);
			if (*threadPointer->isApplicationPlay)
			{

				threadPointer->physicsEngine->Update(deltaTime);
			}


				

			Sleep(threadPointer->sleepTime);
		}

	}


	return 0;

}

void InitializeApplicationThread(float time)
{
	
	applicationThreadExtern->desiredUpdateTime = time;
	applicationThreadExtern->physicsEngine = &PhysicsEngine::GetInstance();
	applicationThreadExtern->manager = &ThreadManager::Getinstance();
	applicationThreadExtern->entityManager = &EntityManager::GetInstance();
	applicationThreadExtern->panelmanager = &PanelManager::GetInstance();
	applicationThreadExtern->isActive = true;
	applicationThreadExtern->sleepTime = 1;

	applicationThreadExtern->threadHandle = CreateThread(
		NULL,						
		0,							
		UpdateApplicationThread,		
		(void*)applicationThreadExtern,			
		0,						
		&applicationThreadExtern->ThreadId);		

	// SoftBody Thread
}
