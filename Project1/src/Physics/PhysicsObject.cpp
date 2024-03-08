#include "PhysicsObject.h"
#include "../Triangle.h"
#include "PhysicsEngine.h"

std::vector<glm::vec3> collisionPoint;
std::vector<glm::vec3> collisionNormal;

PhysicsObject::PhysicsObject(Model* model)
{
	//this->model = model;
	name = "Physics Object";

	acceleration = glm::vec3(0.0f);
	
}

PhysicsObject::PhysicsObject()
{
	name = "Physics Object";

	acceleration = glm::vec3(0.0f);
}

PhysicsObject::~PhysicsObject()
{
	PhysicsEngine::GetInstance().RemovePhysicsObject(this);
}

void PhysicsObject::DrawProperties()
{
	Model::DrawProperties();

	DrawPhysicsObjectProperties();

}

void PhysicsObject::SceneDraw()
{
	Model::SceneDraw();

}

void PhysicsObject::Start()
{
}

void PhysicsObject::Update(float deltaTime)
{
}

void PhysicsObject::OnDestroy()
{
}

void PhysicsObject::Render()
{
	switch (physicsType)
	{
	case SPHERE:
		GraphicsRender::GetInstance().DrawSphere(UpdateSphere().center, UpdateSphere().radius+renderRadius, glm::vec4(0, 0.6f, 0, 1),true);
		break;
	case AABB:
		glm::vec3 center = (UpdateAABB().minV + UpdateAABB().maxV) * 0.5f;

		glm::vec3 scale;

		
		glm::vec3 extents = (UpdateAABB().maxV - UpdateAABB().minV) * 0.5f;

		scale.x = extents.x * 1.0f;
		scale.y = extents.y * 1.0f;
		scale.z = extents.z * 1.0f;

		GraphicsRender::GetInstance().DrawBox(center, scale, glm::vec4(0, 0.6f, 0, 1), true);
		break;
	case MESH_TRIANGLES:
		break;
	default:
		break;
	}
}

void PhysicsObject::update(float deltatime)
{
	glm::vec3 gravity(0.0f, -9.81f* gravityValue, 0.0f);
	acceleration = gravity;
	velocity += acceleration * deltatime;
	transform.position += velocity * deltatime;
	

}

//bool PhysicsObject::checkCollision( PhysicsObject& other)
//{
//
//	
//	switch (physicsType)
//	{
//	case PhysicsType::AABB:
//		if (other.physicsType == AABB)
//		{
//			return CheckCOllisionAABBvsAABB(UpdateAABB(), other.UpdateAABB());
//
//		}
//		else
//		{
//			return CheckSphereAABBCollision(other.UpdateSphere(), UpdateAABB());
//		}
//		break;
//
//	case PhysicsType::SPHERE:
//
//		if (other.physicsType == AABB)
//		{
//			return CheckSphereAABBCollision(UpdateSphere(), other.UpdateAABB());
//		}
//		else if(other.physicsType == SPHERE)
//		{
//			return CheckSpherevsSphereCollision(UpdateSphere(), other.UpdateSphere());
//		}
//		else if(other.physicsType == TRIANGLE)
//		{
//			return CollisionSphereVsMeshOfTriangles(UpdateSphere(), other.model->transform.getModelMatrix(),
//				other.listoftriangles, collisionPoint,collisionNormal);
//
//		}
//
//		break;
//
//	case PhysicsType::TRIANGLE:
//
//		if (other.physicsType == TRIANGLE)
//		{
//			
//		}
//		else
//		{
//			return CheckSpherevsSphereCollision(UpdateSphere(), other.UpdateSphere());
//		}
//
//		break;
//	}
//
//
//
//	return false;
//}


cAABB PhysicsObject::GetModelAABB()
{
	glm::mat4 transformMatrix = transform.GetModelMatrix();


	cAABB localAABB;
	glm::vec3 minPoint = glm::vec3(transformMatrix * glm::vec4(aabb.minV, 1.0f));
	glm::vec3 maxPoint = glm::vec3(transformMatrix * glm::vec4(aabb.maxV, 1.0f));

	localAABB.minV = glm::min(minPoint, maxPoint);
	localAABB.maxV = glm::max(minPoint, maxPoint);




	return localAABB;
}

std::vector<Triangle> PhysicsObject::GetModelTriangleList()
{
	return listoftriangles;
}

const std::vector<cAABB>& PhysicsObject::GetCollisionAABBs()
{
	return collisionAABBs;
}

bool PhysicsObject::CheckCollision(PhysicsObject* other, std::vector<glm::vec3>& collisionPoints, std::vector<glm::vec3>& collisionNormals)

{



	switch (physicsType)
	{
	case PhysicsType::AABB:
		if (other->physicsType == AABB)
		{
			return CheckCOllisionAABBvsAABB(UpdateAABB(), other->UpdateAABB(),collisionPoints,collisionNormals);

		}
		else if(other->physicsType == SPHERE)
		{
			//return CheckSphereAABBCollision(other->UpdateSphere(), UpdateAABB());
			cSphere* updatedSphere = new cSphere(other->UpdateSphere());
			return CheckSphereVSAABBCollision(updatedSphere, UpdateAABB(), false, collisionPoints, collisionNormals);
			
		}
		else if(other->physicsType == MESH_TRIANGLES)
		{
			if (other->isBvhActive)
			{
				return CollisionAABBVsMeshOfTriangles(UpdateAABB(), other->BvhAABBTree->root,
					other->transform.GetModelMatrix(), other->GetModelTriangleList(),
					collisionPoints, collisionNormals, collisionAABBs);
			}
		}

		break;
#pragma region SphereVS
	case PhysicsType::SPHERE:

		if (other->physicsType == AABB)
		{
			cSphere* updatedSphere = new cSphere(UpdateSphere());
			return CheckSphereVSAABBCollision(updatedSphere, other->UpdateAABB(),true,collisionPoints,collisionNormals);
		}
		else if (other->physicsType == SPHERE)
		{
			cSphere* updatedSphere = new cSphere(UpdateSphere());
			cSphere* OtherupdatedSphere = new cSphere(other->UpdateSphere());
			return CheckSphereVSSphereCollision(updatedSphere, OtherupdatedSphere,collisionPoints,collisionNormals);
		}
		else if (other->physicsType == MESH_TRIANGLES)
		{
			if (other->isBvhActive)
			{
				cSphere* updatedSphere = new cSphere(UpdateSphere());
				return CollisionSphereVsMeshOfTriangles(UpdateAABB(), updatedSphere, other->BvhAABBTree->root,
					other->transform.GetModelMatrix(), other->GetModelTriangleList(), collisionPoints, collisionNormals, collisionAABBs);
			}

			return CollisionSphereVsMeshOfTriangles(UpdateSphere(), other->transform.GetModelMatrix(),
				other->listoftriangles, other->triangleSpheres,collisionPoints, collisionNormals);

		}
#pragma endregion
	case PhysicsType:: MESH_TRIANGLES :
		if (other->physicsType == SPHERE)
		{
			return CollisionSphereVsMeshOfTriangles(other->UpdateSphere(),transform.GetModelMatrix(),
				listoftriangles, triangleSpheres,collisionPoints, collisionNormals);
		}

		break;

	//case PhysicsType::TRIANGLE:

	//	if (other->physicsType == TRIANGLE)
	//	{

	//	}
	//	else if (other->physicsType == SPHERE)
	//	{
	//		return CheckSpherevsSphereCollision(UpdateSphere(), other->UpdateSphere());
	//	}

		break;
	}



	return false;
}

cAABB  PhysicsObject:: UpdateAABB()
{

	//cAABB temp;

	glm::vec3 originalMinV = aabb.minV;
	glm::vec3 originalMaxV = aabb.maxV;
	glm::mat4 transformMatrix =transform.GetModelMatrix();

	// Transform the eight vertices of the original AABB
	glm::vec4 vertices[8];
	vertices[0] = transformMatrix * glm::vec4(originalMinV.x, originalMinV.y, originalMinV.z, 1.0f);
	vertices[1] = transformMatrix * glm::vec4(originalMinV.x, originalMinV.y, originalMaxV.z, 1.0f);
	vertices[2] = transformMatrix * glm::vec4(originalMinV.x, originalMaxV.y, originalMinV.z, 1.0f);
	vertices[3] = transformMatrix * glm::vec4(originalMinV.x, originalMaxV.y, originalMaxV.z, 1.0f);
	vertices[4] = transformMatrix * glm::vec4(originalMaxV.x, originalMinV.y, originalMinV.z, 1.0f);
	vertices[5] = transformMatrix * glm::vec4(originalMaxV.x, originalMinV.y, originalMaxV.z, 1.0f);
	vertices[6] = transformMatrix * glm::vec4(originalMaxV.x, originalMaxV.y, originalMinV.z, 1.0f);
	vertices[7] = transformMatrix * glm::vec4(originalMaxV.x, originalMaxV.y, originalMaxV.z, 1.0f);

	// Find the new minimum and maximum corners
	glm::vec3 transformedMinV = glm::vec3(vertices[0]);
	glm::vec3 transformedMaxV = glm::vec3(vertices[0]);

	for (int i = 1; i < 8; ++i) {
		transformedMinV = glm::min(transformedMinV, glm::vec3(vertices[i]));
		transformedMaxV = glm::max(transformedMaxV, glm::vec3(vertices[i]));
	}

	return cAABB(transformedMinV, transformedMaxV);
	
}

cSphere PhysicsObject::UpdateSphere()
{
	glm::vec3 originalCenter = sphereShape.center;
	float orginalRadius = sphereShape.radius;
	glm::mat4 transformMatrix = transform.GetModelMatrix();
	glm::vec4 transformedCenter = transformMatrix * glm::vec4(originalCenter, 1.0f);

	glm::mat4 scaleMatrix = glm::mat4(1.0f); // Initialize the scale matrix
	scaleMatrix[0][0] = transform.scale.x;
	scaleMatrix[1][1] = transform.scale.y;
	scaleMatrix[2][2] = transform.scale.z;

	float maxScale = glm::max(transform.scale.x, glm::max(transform.scale.y, transform.scale.z));
	float updatedRadius = orginalRadius * maxScale;

	return cSphere(glm::vec3(transformedCenter), updatedRadius);
}

void PhysicsObject::CalculateTriangle()
{
	for (cSphere*& s : triangleSpheres)
	{	
		delete s;
	}
	
	listoftriangles.clear();
	triangleSpheres.clear();

	for  (std::shared_ptr<Mesh> mesh : meshes )
	{
		std::vector<Triangle> trianglelist;
		std::vector<cSphere*> meshSphers;

		trianglelist.reserve(mesh->triangle.size());
		meshSphers.reserve(mesh->triangle.size());

		for (const Triangles& triangle : mesh->triangle)
		{
			Triangle temp;
			temp.v1 = triangle.v1;
			temp.v2 = triangle.v2;
			temp.v3 = triangle.v3;
			temp.normal = triangle.normal;
			temp.CalculateMidpoint();

			glm::vec3 sphereCenter = (temp.v1 + temp.v2 + temp.v3) / 3.0f;
			float radius = glm::max(glm::distance(sphereCenter, temp.v1),
				glm::max(glm::distance(sphereCenter, temp.v2), glm::distance(sphereCenter, temp.v3)));

			listoftriangles.push_back(temp);
			triangleSpheres.push_back(new cSphere(sphereCenter, radius));
		}

	}

	
}

 

void PhysicsObject::Initialize(PhysicsType physicsType, bool collision, ObjectMode mode)
{
	this->physicsType = physicsType;
	this->collisionCallbool = collision;
	this->mode = mode;
	//if (this->isKinematic)
	//{
	//	gravityValue = 0;
	//}
	//else
	//{
	//	gravityValue = 0.1f;
	//}
	
	
		aabb = CalculateModelAABB();
		

	

	if (physicsType == SPHERE)
	{
		glm::vec3 position = (aabb.minV + aabb.maxV) * 0.5f;
		glm::vec3 sideLengths = aabb.maxV - aabb.minV;
		float radius = 0.5f * glm::max(sideLengths.x, glm::max(sideLengths.y, sideLengths.z));
		sphereShape =  cSphere(position, radius);
	}

		
	if (physicsType == MESH_TRIANGLES)
	{
		CalculateTriangle();

		BvhAABBTree = new BvhTree(this);
	}
	
	PhysicsEngine::GetInstance().AddPhysicsObjects(this);
}


cAABB PhysicsObject::CalculateModelAABB()
{
	if (meshes.empty())
	{
		return cAABB{ glm::vec3(0.0f), glm::vec3(0.0f) };
	}

	cAABB minMax;

	minMax.minV = meshes[0]->vertices[0].Position;
	minMax.maxV = meshes[0]->vertices[0].Position;

	for (std::shared_ptr<Mesh> mesh : meshes)
	{
		cAABB temp = CalculateAABB(mesh->vertices);

		minMax.minV.x =glm::min(temp.minV.x, minMax.minV.x);
		minMax.minV.y =glm::min(temp.minV.y, minMax.minV.y);
		minMax.minV.z =glm::min(temp.minV.z, minMax.minV.z);
					   
		minMax.maxV.x =glm::max(temp.maxV.x, minMax.maxV.x);
		minMax.maxV.y =glm::max(temp.maxV.y, minMax.maxV.y);
		minMax.maxV.z =glm::max(temp.maxV.z, minMax.maxV.z);
	}

	return cAABB{ minMax.minV, minMax.maxV };
}

glm::vec3 PhysicsObject::GetPosition()
{
	return transform.position;
}

void PhysicsObject::SetPosition(const glm::vec3& Position)
{
	transform.position = Position;
}

const std::function<void(PhysicsObject*)>& PhysicsObject::GetCollisionCall()
{
	return collisionCallback;
}

void PhysicsObject::DoCollisionCall(const std::function<void(PhysicsObject*)>& collisionCallback)
{
	this->collisionCallback = collisionCallback;
}

void PhysicsObject::SetMass(const float& massValue)
{
	this->mass = massValue;
	inverseMass = 1.0f / mass;
}

void PhysicsObject::DrawPhysicsObjectProperties()
{
	
	ImGui::NewLine();
	if (!ImGui::TreeNodeEx("Physics properties", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}


	ImGui::Checkbox("IsEnable", &isEnabled);
	ImGui::SameLine();

	ImGui::NewLine();
	ImGui::Checkbox("IsBvhActive ", &isBvhActive);

	ImGui::Text("Object Mode");
	ImGui::SameLine();
	const char* objectModeOptions[] = { "Static", "Dynamic"};
	ImGui::SetNextItemWidth(200);
	if (ImGui::Combo("##Object Mode", reinterpret_cast<int*>(&mode), objectModeOptions, IM_ARRAYSIZE(objectModeOptions)))
	{
		
	}

	ImGui::Text("Physics Type");
	ImGui::SameLine();
	const char* physicsTypeOptions[] = { "SPHERE", "AABB" };
	ImGui::SetNextItemWidth(200);
	/*if (!ImGui::Combo("##Physics Type", reinterpret_cast<int*>(&physicsType), physicsTypeOptions, IM_ARRAYSIZE(physicsTypeOptions)))
	{

	}*/
	
	ImGui::Text("Bouciness");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(200);
	ImGui::DragFloat("##Bouciness", &bounciness);

	ImGui::TreePop();
}






