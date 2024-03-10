#pragma once
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"../../model.h"
struct Particle
{
    Particle(const glm::vec3& pos, float m) :
        position(pos), velocity(0.0f), mass(m), force(0.0f) {}
    
    glm::vec3 position;
    glm::vec3 velocity;
    float mass;
    glm::vec3 force;
};

struct Spring {
    Particle* particle1;
    Particle* particle2;
    float restLength;
    float stiffness;

    Spring(Particle* p1, Particle* p2, float len, float k) :
        particle1(p1), particle2(p2), restLength(len), stiffness(k)
    {}
};


class SoftBodyMesh : public Model
{
public:
    SoftBodyMesh();
    ~SoftBodyMesh();
    std::vector<Particle*> particles;
    std::vector<Spring*> springs;   

    void addParticle(const glm::vec3& position, float mass);

    void addSpring(Particle* particle1, Particle* particle2, float restLength, float stiffness);

    void update(float deltaTime);

     void DrawProperties()override;
     void SceneDraw()override;

     void Start() override;
     void Update(float deltaTime) override;
     void Render()override;
     void OnDestroy()override;


     void SetUpMesh();

private:

    bool showDebug = true;
};

