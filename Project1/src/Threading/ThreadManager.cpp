#include "ThreadManager.h"



ThreadManager::ThreadManager()
{
	
}

ThreadManager::~ThreadManager()
{
}

ThreadManager& ThreadManager::Getinstance()
{
	

	static ThreadManager instance;
	return instance;
}



void ThreadManager::AddThread(BaseMyThread* panel)
{
	m_listOfThreads.push_back(panel);

}

void ThreadManager::RemoveThread(BaseMyThread* panel)
{
	m_listOfThreads.erase(std::remove(m_listOfThreads.begin(), m_listOfThreads.end(), panel), m_listOfThreads.end());
}

void ThreadManager::Update(float deltaTime)
{

	for (BaseMyThread* threads : m_listOfThreads)
	{
		threads->ThreadUpdate(deltaTime);

	}
}
