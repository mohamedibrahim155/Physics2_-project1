#pragma once
#include <vector>
#include "PhysicsObject.h"
#include"SoftBody/SoftbodyObject.h"



class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	static PhysicsEngine& GetInstance();
	float timer = 0;
	float fixedTimeStep = 0.01f;
	

	void AddPhysicsObjects(PhysicsObject* objs);
	void RemovePhysicsObject(PhysicsObject* objs);
	void RemoveAllPhysicsObject();

	void AddSoftBodyObject(SoftbodyObject* objs);
	void RemoveSoftBodyObject(SoftbodyObject* objs);

	void Update(float deltaTime);
	void UpdatePhysics(float deltatime);
	void UpdateVerlet(float deltatime);
	void UpdateSoftBodiesVertices();


	std::vector<glm::vec3> collisionPoints;
	std::vector<glm::vec3> collisionNormals;
	std::vector<SoftbodyObject*> softbodyObjects;

private:
	std::vector<PhysicsObject*> physicsObjects;

};

