#include <GL/glew.h>
#include <GL/glut.h>
#include "Esqueletillo.h"
#include "EstarEsq.h"
#include "Scene.h"

const float distanciaRecorrido = 2.0f;
enum PlayerAnims
{
	STAND_LEFT
};

Esqueletillo::Esqueletillo(Player* p, const glm::ivec2& peq, int vida, Scene* escena) : EnemigoBase(vida) {
	player = p;
	posEsq = peq;
	sc = escena;
}

void Esqueletillo::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, TileMap* m)
{
	setInCollisionList(false);
	setTileMap(m);
	spritesheet.loadFromFile("images/Skeleton.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(30, 45), glm::vec2(0.75, 1.0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(STAND_LEFT, 4);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.1f, 0.f));

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
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEsq.x), float(tileMapDispl.y + posEsq.y)));
	estado = new EstarEsq(player, &posEsq, tileMapDispl, sprite, map);
}

void Esqueletillo::update(int deltaTime)
{
	/*glm::vec2 ppos = sc->getPlayerPosition();
	glm::vec2 epos = sprite->getPosition();
	glm::ivec2 diff = glm::ivec2(std::abs(ppos.x - epos.x), std::abs(ppos.y - epos.y));
	float dist = std::sqrt(diff.x*diff.x + diff.y*diff.y);
	if (dist < 64 && !inCollisionList)
	{
		sc->getPlayer()->addEnemy(this);
		inCollisionList = true;
	}*/

	EstadoEsq* nuevo = estado->cambiarEstado();
	if (nuevo != NULL) {
		if (nuevo != estado) {
			delete estado;
			estado = nuevo;
		}
	}
	estado->update(deltaTime);
	sprite->update(deltaTime);
}

void Esqueletillo::render()
{
	sprite->render();
}


void Esqueletillo::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Esqueletillo::setPosition(const glm::ivec2 &pos)
{
	posEsq = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEsq.x), float(tileMapDispl.y + posEsq.y)));
}

glm::vec2 Esqueletillo::getRealPosition() {
	return sprite->getPosition();
}

glm::ivec2 Esqueletillo::getPosition() {
	return posEsq;
}

glm::vec2 Esqueletillo::getMapPosition()
{
	glm::vec2 ret = (glm::ivec2(sprite->getPosition()) - tileMapDispl) / 16;
	return glm::vec2(ret.y, ret.x);
}

void Esqueletillo::lastAction() {
	
}