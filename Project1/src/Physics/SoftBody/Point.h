#pragma once
#include "../../Vertex.h"
#include <vector>

struct VertexData
{
	VertexData() {};

	Vertex* vertex = nullptr;
	glm::vec3 offset;
};
struct Stick;

struct Point
{
	//public:
	Point() {};
	Point(glm::vec3 position, glm::vec3 oldPostiion, std::vector<VertexData*> _vertex) :
		position(position), previousPosition(oldPostiion), vertex(_vertex)
	{
	}

	glm::vec3 position = glm::vec3(0);
	glm::vec3 previousPosition = glm::vec3(0);
	glm::vec3 velocity = glm::vec3(0);
	glm::vec3 centre = glm::vec3(0);
	std::vector<Stick*> connectedSticks;
	float radius = 0.005f;
	 std::vector<VertexData*> vertex;
	bool locked = false;

};


