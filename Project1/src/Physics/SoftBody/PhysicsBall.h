#pragma once
#include "../../InputManager/iInputOberver.h"
#include "../../model.h"

class PhysicsBall : public Model, public iInputObserver
{
	PhysicsBall();
	~PhysicsBall();


	



	// Inherited via iInputObserver
	void OnKeyPressed(const int& key) override;

	void OnKeyReleased(const int& key) override;

	void OnKeyHold(const int& key) override;

};

