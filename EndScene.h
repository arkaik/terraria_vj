#pragma once

#include "BasicScene.h"
#include "ShaderProgram.h"
#include "Sprite.h"
#include <iostream>


class EndScene : public BasicScene
{
public:
	EndScene();
	~EndScene();

	void init();
	void update(int deltatime);
	void render();
	BasicScene* changeState();
private:
	void initShaders();
	ShaderProgram texProgram;
	glm::mat4 projection;

	Sprite* end;
	Sprite* anywhere;
	Sprite* background;

	bool bmenu;
};