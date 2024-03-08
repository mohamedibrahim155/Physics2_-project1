#pragma once
#include "../model.h"
//#include "PhysicsCollisionTypes.h"
#include <functional>
#include "BvhTree.h"

enum PhysicsType
{
	SPHERE = 0,
	AABB = 1,
	MESH_TRIANGLES = 2, 
	//MESH
};


enum ObjectMode
{
	STATIC,
	DYNAMIC
};


class PhysicsObject  : public Model
{
public:
	PhysicsObject();
	PhysicsObject(Model* model);
	~PhysicsObject();

	PhysicsType physicsType;
	ObjectMode mode = STATIC;

	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 velocity = glm::vec3(0);
	glm::vec3 acceleration;

	bool isKinematic;
	bool collisionCallbool;
	bool isBvhActive = true;

	float gravityValue = 0.1f;
	float inverseMass = 1.0f;
	float bounciness = 0.8f;
	float mass = 1.0f;

	std::function<void(PhysicsObject*)> collisionCallback = nullptr;
	std::vector<cSphere*>  triangleSpheres;
	std::vector<cAABB>  collisionAABBs;
	std::vector<Triangle> listoftriangles;

	cAABB aabb;
	cSphere sphereShape;
	BvhTree* BvhAABBTree;

	void Initialize(PhysicsType physicsType = PhysicsType::AABB, bool collision = false, ObjectMode mode = ObjectMode::STATIC);

	 void DrawProperties() override;
	 void SceneDraw() override;

	 void Start() override;
	 void Update(float deltaTime) override;
	 void OnDestroy();
	 void Render() override;

	 void update(float deltatime);
	 void CalculateTriangle();
	 void SetPosition(const glm::vec3& Position);
	 void DoCollisionCall(const std::function<void(PhysicsObject*)>& collisionCallback);
	 void SetMass(const float& massValue);
	
	cAABB UpdateAABB();
	cAABB GetModelAABB();
	cAABB CalculateModelAABB();

	cSphere UpdateSphere();

	bool CheckCollision(PhysicsObject* other, std::vector<glm::vec3>& collisionPoints, std::vector<glm::vec3>& collisionNormals);
	
	std::vector<Triangle> GetModelTriangleList();
	const std::vector<cAABB>& GetCollisionAABBs();

	const std::function<void(PhysicsObject*)>& GetCollisionCall();
	//bool checkCollision( PhysicsObject& other);
	glm::vec3 GetPosition();


private:


	void DrawPhysicsObjectProperties();

	float renderRadius = 0.01;

};



