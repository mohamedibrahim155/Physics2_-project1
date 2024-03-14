#include "PhysicsBall.h"
#include "../../InputManager/InputManager.h"

PhysicsBall::PhysicsBall()
{

	InputManager::GetInstance().AddObserver(this);
}

PhysicsBall::~PhysicsBall()
{
}

void PhysicsBall::OnKeyPressed(const int& key)
{
    if (key == GLFW_KEY_W)
    {
        transform.position.z += 1.0f;
    }


    if (key == GLFW_KEY_A)
    {
        transform.position.x += 1.0f;

    }


    if (key == GLFW_KEY_S)
    {
        transform.position.z -= 1.0f;

    }


    if (key == GLFW_KEY_D)
    {
        transform.position.x -= 1.0f;

    }

}

void PhysicsBall::OnKeyReleased(const int& key)
{
}

void PhysicsBall::OnKeyHold(const int& key)
{
}
