#include "EndScene.h"
#include "MenuScene.h"
#include "Game.h"

EndScene::EndScene()
{
	anywhere = NULL;
}

EndScene::~EndScene()
{
	if (anywhere != NULL)
		delete anywhere;

}

void EndScene::init()
{
	initShaders();
	bmenu = false;
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	anywhere = Sprite::createSprite("images/gui.png", glm::vec4(288, 320, 192, 32), &texProgram);
	anywhere->setPosition(450, 300);
}

void EndScene::update(int deltatime)
{
	if (Game::instance().getReleasedMouseKey(0)) {
		bmenu = true;
	}
}

void EndScene::render()
{
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	//texProgram.setUniformMatrix4f("ftcMatrix", ftcMatrix);
	texProgram.default();

	anywhere->render();
}

BasicScene * EndScene::changeState()
{
	if (bmenu) {
		BasicScene* bs = new MenuScene();
		bs->init();
		return bs;
	}
	return this;
}

void EndScene::initShaders()
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
