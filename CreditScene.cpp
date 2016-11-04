#include "CreditScene.h"
#include "MenuScene.h"
#include "Game.h"

CreditScene::CreditScene()
{
	n1 = NULL;
	n2 = NULL;
}

CreditScene::~CreditScene()
{
	if (n1 != NULL)
		delete n1;
	if (n2 != NULL)
		delete n2;
}

void CreditScene::init()
{
	initShaders();

	bmenu = false;
	
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	n1 = Sprite::createSprite("images/gui.png",glm::vec4(0,320, 288, 64), &texProgram);
	//n1->setOrigin(140,32);
	n1->setPosition(400, 400);
	n2 = Sprite::createSprite("images/gui.png", glm::vec4(0, 384, 256, 64), &texProgram);
	//n2->setOrigin(126, 32);
	n2->setPosition(400, 450);

	background = Sprite::createSprite("images/MapBG11.png", glm::vec4(0, 0, 112, 65), &texProgram);
	background->setScale(glm::vec2(12, 12));
}

void CreditScene::update(int deltatime)
{
	if (Game::instance().getReleasedKey(27)) {
		bmenu = true;
	}
}

void CreditScene::render()
{
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	//texProgram.setUniformMatrix4f("ftcMatrix", ftcMatrix);
	texProgram.default();

	background->render();
	n1->render();
	n2->render();
}

BasicScene * CreditScene::changeState()
{
	if (bmenu) {
		BasicScene* bs = new MenuScene();
		bs->init();
		return bs;
	}
	return this;
}

void CreditScene::initShaders()
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