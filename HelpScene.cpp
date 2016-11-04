#include "HelpScene.h"

HelpScene::HelpScene()
{
	instructions = NULL;
}

HelpScene::~HelpScene()
{
	if (instructions != NULL)
		delete instructions;
}

void HelpScene::init()
{
	bmenu = false;

	initShaders();

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	instructions = Sprite::createSprite("images/gui.png", glm::vec4(128, 0, 352, 320), &texProgram);
	//n1->setOrigin(140,32);
	instructions->setPosition(450, 200);

	anywhere = Sprite::createSprite("images/gui.png", glm::vec4(288, 320, 192, 32), &texProgram);
	anywhere->setPosition(450, 550);

	background = Sprite::createSprite("images/MapBG1.png", glm::vec4(0, 0, 112, 65), &texProgram);
	background->setScale(glm::vec2(12, 12));
}

void HelpScene::update(int deltatime)
{
	if (Game::instance().getReleasedKey(27)) {
		bmenu = true;
	}
}

void HelpScene::render()
{
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	//texProgram.setUniformMatrix4f("ftcMatrix", ftcMatrix);
	texProgram.default();

	background->render();
	instructions->render();
	anywhere->render();
}

BasicScene * HelpScene::changeState()
{
	if (bmenu) {
		BasicScene* bs = new MenuScene();
		bs->init();
		return bs;
	}
	return this;
}

void HelpScene::initShaders()
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
