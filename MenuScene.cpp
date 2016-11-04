#include "MenuScene.h"
#include "Scene.h"
#include "HelpScene.h"
#include "CreditScene.h"
#include "Game.h"

MenuScene::MenuScene()
{
	button1 = NULL;
	button2 = NULL;
	button3 = NULL;
	button4 = NULL;
	background = NULL;
}

MenuScene::~MenuScene()
{
	if (button1 != NULL)
		delete button1;

	if (button2 != NULL)
		delete button2;

	if (button3 != NULL)
		delete button3;

	if (button4 != NULL)
		delete button4;

	if (background != NULL)
		delete background;
}

void MenuScene::init()
{
	initShaders();

	bplay = false;
	bhelp = false;
	bcredit = false;
	bexit = false;

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	button1 = Sprite::createSprite("images/gui.png", glm::vec4(0, 0, 64, 32), &texProgram);
	button1->setPosition(550, 250);
	button2 = Sprite::createSprite("images/gui.png", glm::vec4(0, 128, 64, 32), &texProgram);
	button2->setPosition(550, 300);
	button3 = Sprite::createSprite("images/gui.png", glm::vec4(0, 64, 96, 32), &texProgram);
	button3->setPosition(550, 350);
	button4 = Sprite::createSprite("images/gui.png", glm::vec4(0, 192, 64, 32), &texProgram);
	button4->setPosition(550, 400);

	background = Sprite::createSprite("images/MapBG9.png", glm::vec4(0, 0, 112, 65), &texProgram);
	background->setScale(glm::vec2(12,12));
}

void MenuScene::update(int deltatime)
{
	if (Game::instance().getReleasedMouseKey(0))
	{
		glm::vec2 ppos = Game::instance().getMousePosition();
		if (ppos.y < 300 && ppos.y > 250 && ppos.x > 500)
			bplay = true;
		else if (ppos.y < 350 && ppos.y > 300 && ppos.x > 500)
			bhelp = true;
		else if (ppos.y < 400 && ppos.y > 350 && ppos.x > 500)
			bcredit = true;
		else if (ppos.y < 450 && ppos.y > 400 && ppos.x > 500)
			Game::instance().exit();
	}
	
}

void MenuScene::render()
{
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	//texProgram.setUniformMatrix4f("ftcMatrix", ftcMatrix);
	texProgram.default();

	background->render();

	button1->render();
	button2->render();
	button3->render();
	button4->render();
}

BasicScene* MenuScene::changeState()
{
	//cout << "Changing from MenuScene" << endl;
	if (bplay) {
		BasicScene* bs = new Scene();
		bs->init();
		return bs;
	}
	else if (bhelp) {
		BasicScene* bs = new HelpScene();
		bs->init();
		return bs;
	}
	else if (bcredit) {
		BasicScene* bs = new CreditScene();
		bs->init();
		return bs;
	}
	return this;
}

void MenuScene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
	GLenum error = glGetError();
}
