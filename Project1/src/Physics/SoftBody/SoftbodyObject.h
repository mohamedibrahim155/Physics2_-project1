#pragma once
#include "../../model.h"
#include "../PhysicsCollisionTypes.h"
#include"../PhysicsObject.h"
#include "Stick.h"



enum class BodyType
{
	CLOTH = 0,
	SPRING = 1
};

class SoftbodyObject : public Model
{
public:
	SoftbodyObject();
	~SoftbodyObject();

	bool isSoftBodyActive = true;

	float gravity = 0.1f /*-9.81f*/;

	BodyType type = BodyType::CLOTH;

	std::vector<Triangle> listOfTriangles;
	std::vector<Point*> listOfPoints;
	std::vector<Stick*> listOfSticks;
	std::vector<Triangle> GetTriangleList();

	void Initialize();
	void CalculateCloth();
	void CalculateSpring();
	void SetupPoints(std::vector<Vertex>& vertices);
	void SetupSticks(std::shared_ptr<Mesh> mesh, unsigned int currentMeshIndex);


	void DrawProperties()override;
	void SceneDraw()override;

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;
	void OnDestroy() override;

	void UpdateVerlet(float deltaTime);
	void UpdateSticks(float deltaTime);
	void UpdatePoints(float deltaTime);

	void CollisionTest();
	void UpdateVertices();
	void UpdateNormals();

	void CleanZeros(glm::vec3& value);
	void AddLockSphere(glm::vec3 centre, float radius);

	PhysicsObject* updateAABBTest = nullptr;
private:

	bool showDebug = true;

	float renderRadius = 0.025f;
	float tightnessFactor = 1;
	float lockRadius;
	const double MAX_DELTATIME = 1.0 / 60.0;

	glm::vec3 downVector = glm::vec3(0, -1, 0);
	glm::vec3 lockSphereCenter;
	
	bool CheckSoftBodyAABBCollision(Point* point, const cAABB& aabb);
	bool CheckSoftBodySphereCollision(Point* point, const cSphere& sphere);
	void HandleSoftBodySphereCollision(Point*& point, const cSphere& sphere);
	//bool CheckSoftBodyAABBCollision(const cAABB& aabb);
	

	void HandleSoftBodyAABBCollision(Point& particle, const cAABB& aabb);

	bool IsPointLocked(Point* point, glm::vec3 centre, float radius);

};

