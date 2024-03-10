#include "SoftBodyMesh.h"
#include "../../GraphicsRender.h"
SoftBodyMesh::SoftBodyMesh()
{
}
SoftBodyMesh::~SoftBodyMesh()
{
}
void SoftBodyMesh::addParticle(const glm::vec3& position, float mass)
{
    particles.push_back(new Particle(position, mass));
}

void SoftBodyMesh::addSpring(Particle* particle1, Particle* particle2, float restLength, float stiffness)
{
    springs.push_back(new Spring(particle1, particle2, restLength, stiffness));
}



void SoftBodyMesh::update(float deltaTime)
{
    const float groundThreshold = -2.0f;
    const float damping = 0.1f;

   
    glm::vec3 averageVelocity(0.0f);
    for (Particle* particle : particles) 
    {
        averageVelocity += particle->velocity;
    }
    averageVelocity /= static_cast<float>(particles.size());

    // Iterate over particles
    for (Particle* particle : particles) {

        particle->force += glm::vec3(0.0f, -9.8f * particle->mass, 0.0f);

      
        particle->velocity += (particle->force / particle->mass) * deltaTime;
        particle->position += particle->velocity * deltaTime;

       
        particle->velocity *= 1.0f - damping * deltaTime;


        particle->force = glm::vec3(0.0f);

        if (particle->position.y < groundThreshold) 
        {
           
            particle->position.y = groundThreshold;
            particle->velocity.y *= -0.8f; 
        }
    }

    for (Spring* spring : springs)
    {
        glm::vec3 deltaPos = spring->particle2->position - spring->particle1->position;
        float currentLength = glm::length(deltaPos);

       
        glm::vec3 force = spring->stiffness * (currentLength - spring->restLength) * glm::normalize(deltaPos);

        
        spring->particle1->force += force;
        spring->particle2->force -= force;
    }
}


void SoftBodyMesh::DrawProperties()
{
    Model::DrawProperties();
}

void SoftBodyMesh::SceneDraw()
{
    Model::SceneDraw();
}

void SoftBodyMesh::Start()
{
    
}

void SoftBodyMesh::Update(float deltaTime)
{
    update(deltaTime);
}

void SoftBodyMesh::Render()
{
    if (!showDebug)
    {
        return;
    }
    for ( Particle* particle :  particles)
    {
        GraphicsRender::GetInstance().DrawSphere(particle->position, 0.015f,
            glm::vec4(1, 0, 1, 0));
    }

    for ( Spring* spring :  springs)
    {
      //  GraphicsRender::GetInstance().DrawLine(spring->particle1->position, spring->particle2->position, glm::vec4(1, 1, 0, 1));
    }
}

void SoftBodyMesh::OnDestroy()
{
}

void SoftBodyMesh::SetUpMesh()
{
    glm::vec3 totalPosition = glm::vec3(0);

    glm::mat4 transformedMatrix = transform.GetModelMatrix();

    int currentMeshIndex = 0;
    for (std::shared_ptr<Mesh> mesh : meshes)
    {

        for (Vertex& vertex : mesh->vertices)
        {
            glm::vec4 vertexPosition = glm::vec4(vertex.Position, 1);
            vertexPosition = transformedMatrix * vertexPosition;


            //vertex.Position.x = vertexPosition.x;
            //vertex.Position.y = vertexPosition.y;
            //vertex.Position.z = vertexPosition.z;

            vertex.Position = glm::vec3(vertexPosition);

        }


        for (Vertex& vertex : mesh->vertices)
        {
            addParticle(vertex.Position, 1);
        }

        for (int i = 0; i < mesh->indices.size(); i += 3)
        {
            Particle* point1 = particles[mesh->indices[currentMeshIndex + i]];
            Particle* point2 = particles[mesh->indices[currentMeshIndex + i + 1]];
            Particle* point3 = particles[mesh->indices[currentMeshIndex + i + 2]];

            float restLength = glm::distance(point1->position, point2->position);

            addSpring(point1, point2, restLength, 10);

            restLength = glm::distance(point2->position, point3->position);
            addSpring(point2, point3, restLength, 10);

            restLength = glm::distance(point3->position, point1->position);
            addSpring(point3, point1, restLength, 10);
        }
        currentMeshIndex++;
    }
}
