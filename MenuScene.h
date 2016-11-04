#pragma once

#include "BasicScene.h"
#include "Sprite.h"

class MenuScene : public BasicScene
{
public:
	MenuScene();
	~MenuScene();

	void init();
	void update(int deltatime);
	void render();
	BasicScene* changeState();

private:
	void initShaders();
	ShaderProgram texProgram;
	glm::mat4 projection;
	Sprite* button1;
	Sprite* button2;
	Sprite* button3;
	Sprite* button4;

	Sprite* background;

	bool bplay;
	bool bhelp;
	bool bcredit;
	bool bexit;
};
