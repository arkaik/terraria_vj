#include "Health.h"

void Health::init(ShaderProgram & sp)
{
	h_mid = vector<glm::vec2>(10);
	for (int i = 0; i < int(h_mid.size()); i++)
		h_mid[i] = glm::vec2(650+35 * i, 56);

	tex = *TextureFactory::instance().getTexture("images/items.png");

	h_cor = vector<Sprite*>(10);
	for (int i = 0; i < int(h_cor.size()); i++) {
		h_cor[i] = Sprite::createSprite(&tex, glm::vec4(64, 128, 32, 32), &sp);
		h_cor[i]->setPosition(h_mid[i]);
		h_cor[i]->setOrigin(16, 16);
		h_cor[i]->setFixToCamera(true);
	}

	if (!thealth.init("fonts/AndyBold.ttf", &sp))
		std::cout << "Could not load font!!!" << endl;
	thealth.setSize(28);
	thealth.setPosition(h_mid[0] + glm::vec2(100, -55));
	thealth.setText("Life: 100/100");
}

void Health::update(int deltatime)
{
}

void Health::render()
{
	for (int i = 0; i < int(h_cor.size()); i++)
		h_cor[i]->render();

	//thealth.render();
}