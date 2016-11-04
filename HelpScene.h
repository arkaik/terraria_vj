#pragma once
#include "BasicScene.h"
#include "Sprite.h"
#include "Game.h"
#include <iostream>

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
	void initShaders();
	ShaderProgram texProgram;
	glm::mat4 projection;
	Sprite* instructions;
	Sprite* background;
	Sprite* anywhere;
	bool bmenu;
};
