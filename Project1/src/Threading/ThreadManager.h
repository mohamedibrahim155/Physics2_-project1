#pragma once
#include "BaseMyThread.h"
#include <vector>


class ThreadManager
{
public:

	ThreadManager();
	~ThreadManager();

	static ThreadManager& Getinstance();

	void AddThread(BaseMyThread* panel);
	void RemoveThread(BaseMyThread* panel);	

	void Update(float deltaTime);
private:


	
	std::vector <BaseMyThread*> m_listOfThreads;
	
};

