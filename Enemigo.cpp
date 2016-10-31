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
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};

Enemigo::Enemigo(Scene* escena) {
	sc = escena;
}

void Enemigo::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
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

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemigo.x), float(tileMapDispl.y + posEnemigo.y)));
	estado = new Estar(sc, &posEnemigo, tileMapDispl,sprite);
}

void Enemigo::update(int deltaTime)
{
	sprite->update(deltaTime);
	Estado* nuevo = estado->cambiarEstado();
	if (nuevo != NULL) {
		if (nuevo != estado) {
			delete estado;
			estado = nuevo;
		}
	}
	//estado->update();
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
	estado->setPosition(&posEnemigo);
}

glm::vec2 Enemigo::getPosition() {
	return sprite->getPosition();
}

