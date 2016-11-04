#pragma once

#include "BasicScene.h"
#include "Sprite.h"
#include <iostream>

class CreditScene : public BasicScene
{
public:
	CreditScene();
	~CreditScene();

	void init();
	void update(int deltatime);
	void render();
	BasicScene* changeState();

private:
	void initShaders();
	ShaderProgram texProgram;
	glm::mat4 projection;
	Sprite* n1;
	Sprite* n2;
	Sprite* background;
	Sprite* anywhere;
	bool bmenu;
};
