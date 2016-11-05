#include <GL/glew.h>
#include <GL/glut.h>
#include "Abeja.h"
#include "EstarEsq.h"

const float distanciaRecorrido = 2.0f;
enum PlayerAnims
{
	STAND_LEFT
};

enum AbState {STAY, ATTACK};

Abeja::Abeja(Player* p, const glm::ivec2& peq, int vida) : EnemigoBase(vida) {
	player = p;
	posAb = peq;
	state = STAY;
	tocado = false;
	velocidad = 0;
	haAtacado = false;
	direccion.x = 0;
	direccion.y = 0;
	delay = 0;
	delayMax = 100;
}

void Abeja::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, TileMap* m)
{
	setTileMap(m);
	radioDeteccionPlayer = 10.0f*map->getTileSize();
	spritesheet.loadFromFile("images/enchanted_sword.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(58, 60), glm::vec2(1.0, 1.0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(STAND_LEFT, 4);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));

	/*sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.25f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.5f));*/

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posAb.x), float(tileMapDispl.y + posAb.y)));
}

void Abeja::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (state == STAY && jugadorCerca()) {
		state = ATTACK;
		delay = 0;
	}
	else if (state == ATTACK && !jugadorCerca()) state = STAY;
	if (state == ATTACK) {
		if (haAtacado) {
			++delay;
			if (delay == delayMax) {
				delay = 0;
				haAtacado = false;
			}
		}
		else hacerAtaque(deltaTime);

	}
}

void Abeja::render()
{
	sprite->render();
}


void Abeja::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Abeja::setPosition(const glm::ivec2 &pos)
{
	posAb = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posAb.x), float(tileMapDispl.y + posAb.y)));
}

glm::vec2 Abeja::getRealPosition() {
	return sprite->getPosition();
}

glm::ivec2 Abeja::getPosition() {
	return posAb;
}

glm::vec2 Abeja::getMapPosition()
{
	glm::vec2 ret = (glm::ivec2(sprite->getPosition()) - tileMapDispl) / 16;
	return glm::vec2(ret.y, ret.x);
}

bool Abeja::jugadorCerca() {
	//x+y = rdp es la circumferencia si x^2+y^2 <= rdp^2 esta dentro sino fuera

	glm::vec2 posP = player->getPosition();//Coordenadas reales;
	glm::vec2 posE = glm::vec2(posAb.x + float(tileMapDispl.x), posAb.y + float(tileMapDispl.y));//Coordenadas reales;;
	glm::vec2 pp = glm::vec2(posP.x - posE.x, posP.y - posE.y);
	return pp.x*pp.x + pp.y*pp.y <= radioDeteccionPlayer*radioDeteccionPlayer;
}

void Abeja::hacerAtaque(int deltaTime) {
	glm::vec2 posP = player->getPosition();//Coordenadas reales
	if (velocidad <= 0) {//Comienzo embestida
		if (tocado) {
			haAtacado = true;
			tocado = false;
		}
		posPlayerAnterior = posP;
		posEnemigoAnterior = glm::vec2(posAb.x, posAb.y);
		velocidad = 1;
		direccion.x = posP.x - posAb.x; direccion.y = posP.y - posAb.y;
		float hyp = sqrt(direccion.x*direccion.x + direccion.y*direccion.y);
		if (hyp != 0) {
			direccion.x /= hyp;
			direccion.y /= hyp;
		}
		else direccion.x = direccion.y = 0;
	}
	else {//Si en medio de embestida
		if (!tocado) { velocidad += 8; }
		else { velocidad -= 500; }
	}
	posAb.x = posAb.x + velocidad*float(deltaTime) / 1000.f*direccion.x;
	posAb.y = posAb.y + velocidad*float(deltaTime) / 1000.f*direccion.y;
	if (!tocado) tocado = distanciaActualVsDistanciaAnterior(posP);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posAb.x), float(tileMapDispl.y + posAb.y)));
}


bool Abeja::distanciaActualVsDistanciaAnterior(const glm::vec2 posP) {
	return ((posPlayerAnterior.x - posEnemigoAnterior.x)*(posPlayerAnterior.x - posEnemigoAnterior.x) +
		(posPlayerAnterior.y - posEnemigoAnterior.y)*(posPlayerAnterior.y - posEnemigoAnterior.y)) <=
		((posEnemigoAnterior.x - posAb.x)*(posEnemigoAnterior.x - posAb.x) +
		(posEnemigoAnterior.y - posAb.y)*(posEnemigoAnterior.y - posAb.y));
}

float Abeja::getWidth() { return 30.0f; }
float Abeja::getHeight() { return 35.0f; }