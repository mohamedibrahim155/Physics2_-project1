#include "ChainChomp.h"
#include "../../InputManager/InputManager.h"
ChainChomp::ChainChomp()
{
    CreateChainChomp();
	InputManager::GetInstance().AddObserver(this);
}

ChainChomp::~ChainChomp()
{
}

void ChainChomp::CreateChainChomp()
{


    
    LoadModel("Models/Chain/chain4.fbx");
    name = "Chain Chomp";

    transform.SetPosition(glm::vec3(0, 1, 0));
    transform.SetScale(glm::vec3(0.25f));
    GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().defaultShader);

    type = BodyType::SPRING;
    Initialize();

    AddLockIndexSphere(7, 0.01f);

}

void ChainChomp::ChompMovement()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    float randomX = static_cast<float>(std::rand()) / RAND_MAX * 20.0f - 10.0f;
    float randomY = static_cast<float>(std::rand()) / RAND_MAX * 20.0f - 10.0f;
    float randomZ = static_cast<float>(std::rand()) / RAND_MAX * 20.0f - 10.0f;

    glm::vec3 randomDirection = glm::normalize(glm::vec3(randomX, randomY, randomZ));

    MovePoint(0)->position += randomDirection;


}

void ChainChomp::OnKeyPressed(const int& key)
{
    if (key == GLFW_KEY_Q)
    {
        ChompMovement();
    }
 
}

void ChainChomp::OnKeyReleased(const int& key)
{
}

void ChainChomp::OnKeyHold(const int& key)
{
}
