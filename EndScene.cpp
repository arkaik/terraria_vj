#include "EndScene.h"

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
	anywhere = Sprite::createSprite("images/gui.png", glm::vec4(288, 320, 192, 32), &texProgram);
}

void EndScene::update(int deltatime)
{
}

void EndScene::render()
{
	anywhere->render();
}

BasicScene * EndScene::changeState()
{
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
