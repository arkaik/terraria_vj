#include "Health.h"

Health::Health()
{
	thealth = NULL;
}

Health::~Health()
{
	if (thealth != nullptr)
		delete thealth;
}

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

	health_points = 10;

	thealth = Sprite::createSprite("images/gui.png", glm::vec4(0, 256, 64, 32), &sp);
	thealth->setPosition(glm::vec2(780, 5));
	thealth->setFixToCamera(true);
}

void Health::update(int deltatime)
{
}

void Health::render()
{
	for (int i = 0; i < health_points - 1; i++)
		h_cor[i]->render();

	thealth->render();
}

void Health::decrementLife()
{
	if (health_points > 0) --health_points;
}

void Health::decrementLife(int hp)
{
	health_points -= hp;
	if (health_points < 0) health_points = 0;
}

void Health::incrementLife()
{
	health_points += 1;
	if (health_points > 10) health_points = 10;
}

int Health::getPoints()
{
	return health_points;
}
