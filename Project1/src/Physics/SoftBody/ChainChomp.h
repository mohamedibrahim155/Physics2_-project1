#pragma once
#include "SoftbodyObject.h"
#include "../../InputManager/iInputOberver.h"

class ChainChomp : public SoftbodyObject, public iInputObserver
{

public:
	ChainChomp();
	~ChainChomp();


	void CreateChainChomp();
	void ChompMovement();


	// Inherited via iInputObserver
	void OnKeyPressed(const int& key) override;

	void OnKeyReleased(const int& key) override;

	void OnKeyHold(const int& key) override;

};

