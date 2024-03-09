#pragma once
#include <Windows.h>
#include "../Physics/PhysicsEngine.h"
#include "ThreadManager.h"
#include "../EntityManager/EntityManager.h"
#include "../ImGui/PanelManager.h"


struct ApplicationThread // SoftBody Struct Infor
{
	PhysicsEngine* physicsEngine;
    ThreadManager* manager;
    EntityManager* entityManager;
    PanelManager* panelmanager;


    double desiredUpdateTime = 0.0;  
    bool isThreadActive = false;	
    bool isActive = true;
    bool* isApplicationPlay = nullptr;
    DWORD sleepTime;	

    DWORD ThreadId = 0;
    HANDLE threadHandle = 0;
    CRITICAL_SECTION cs;

};