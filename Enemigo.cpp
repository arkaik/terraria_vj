#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemigo.h"
#include "Game.h"
#include "Estar.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

#include "Scene.h"

enum EnemigoAnims
{
	 STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, STAND, MOVE, STAND_F, MOVE_F
};

//STAND_F, MOVE_F, STAND, MOVE,

Enemigo::Enemigo(Scene* escena, const glm::ivec2 &pos, int vida) : EnemigoBase(vida) {
	sc = escena;
	posEnemigo = pos;
	f = 7;
	delay = 0;
	delayMax = 20;
}

void Enemigo::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	setInCollisionList(false);
	name = "Boss";
	spritesheet.loadFromFile("images/eye.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(110, 162), glm::vec2(0.107, 0.632), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(0, 4);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(1, 4);
	sprite->addKeyframe(1, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(1, glm::vec2(0.108f, 0.f));
	sprite->addKeyframe(1, glm::vec2(0.214f, 0.f));

	sprite->setAnimationSpeed(2, 4);
	sprite->addKeyframe(2, glm::vec2(0.321f, 0.f));

	sprite->setAnimationSpeed(3, 4);
	sprite->addKeyframe(3, glm::vec2(0.321f, 0.f));
	sprite->addKeyframe(3, glm::vec2(0.428f, 0.f));
	sprite->addKeyframe(3, glm::vec2(0.535f, 0.f));

	sprite->changeAnimation(1);

/*	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.25f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.5f));

	spritesheet.loadFromFile("images/bub.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);


	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.25f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.5f));

	sprite->changeAnimation(0);*/
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemigo.x), float(tileMapDispl.y + posEnemigo.y)));
	estado = new Estar(sc, &posEnemigo, tileMapDispl,sprite, &vida);
}

void Enemigo::update(int deltaTime)
{
	glm::vec2 ppos = sc->getPlayerPosition();
	glm::ivec2 diff = glm::ivec2(std::abs(ppos.x - posEnemigo.x), std::abs(ppos.y - posEnemigo.y));
	float dist = std::sqrt(diff.x*diff.x + diff.y*diff.y);
	if (dist < 194 && !inCollisionList)
	{
		sc->getPlayer()->addEnemy(this);
		inCollisionList = true;
	}

	/*if (sc->getPlayer()->overlap(glm::vec4(sprite->getPosition(), 100, 200))) {
		//std::cout << "overlap" << std::endl;
		if (delay == 0) {
			sc->getPlayer()->decrementLife();
			//std::cout << " life " << sc->getPlayer()->getHealthPoints() << std::endl;
		}
		++delay;
		if (delay == delayMax) delay = 0;
	}
	else delay = 0;*/
	
	sprite->update(deltaTime);
	Estado* nuevo = estado->cambiarEstado();
	if (nuevo != NULL) {
		if (nuevo != estado) {
			delete estado;
			estado = nuevo;
		}
	}
	estado->update(deltaTime);
}

void Enemigo::render()
{
	sprite->render();
}

void Enemigo::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Enemigo::setPosition(const glm::vec2 &pos)
{
	posEnemigo = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemigo.x), float(tileMapDispl.y + posEnemigo.y)));
}

glm::vec2 Enemigo::getPosition() {
	return sprite->getPosition();
}

void Enemigo::lastAction() {
	sc->theEnd();
}

float Enemigo::getWidth(){ return 100; }

float Enemigo::getHeight() { return 200; }
