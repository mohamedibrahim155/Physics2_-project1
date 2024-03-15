#include "PhysicsBall.h"
#include "../../InputManager/InputManager.h"

PhysicsBall::PhysicsBall()
{


    ballPhysics = new PhysicsObject();
    ballPhysics->LoadModel("Models/DefaultSphere/DefaultSphere.fbx");
    ballPhysics->name = "BallPhysics";
    ballPhysics->transform.SetPosition(glm::vec3(0, -1, 0.5f));
    ballPhysics->transform.SetScale(glm::vec3(0.25f));
    GraphicsRender::GetInstance().AddModelAndShader(ballPhysics, GraphicsRender::GetInstance().defaultShader);

    ballPhysics->Initialize(SPHERE, true, STATIC);
	InputManager::GetInstance().AddObserver(this);


}

PhysicsBall::~PhysicsBall()
{


}

void PhysicsBall::OnKeyPressed(const int& key)
{
    if (key == GLFW_KEY_T)
    {
        ballPhysics->transform.position.z += 0.3f;
    }


    if (key == GLFW_KEY_F)
    {
        ballPhysics->transform.position.x += 0.3f;

    }


    if (key == GLFW_KEY_G)
    {
        ballPhysics->transform.position.z -= 0.3f;

    }


    if (key == GLFW_KEY_H)
    {
        ballPhysics->transform.position.x -= 0.3f;

    }

}

void PhysicsBall::OnKeyReleased(const int& key)
{
}

void PhysicsBall::OnKeyHold(const int& key)
{
    
   
}
