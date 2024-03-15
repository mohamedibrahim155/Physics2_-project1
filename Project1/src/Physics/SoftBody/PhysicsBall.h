#pragma once
#include "../../InputManager/iInputOberver.h"
#include "../../model.h"
#include "../../Physics/PhysicsObject.h"

class PhysicsBall : public Model, public iInputObserver
{

public:
	PhysicsBall();
	~PhysicsBall();


	
	PhysicsObject* ballPhysics;



	// Inherited via iInputObserver
	void OnKeyPressed(const int& key) override;

	void OnKeyReleased(const int& key) override;

	void OnKeyHold(const int& key) override;

private:



};

