#pragma once
#include "BasicScene.h"

class HelpScene : public BasicScene
{
public:
	HelpScene();
	~HelpScene();

	void init();
	void update(int deltatime);
	void render();
	BasicScene* changeState();

private:

};
