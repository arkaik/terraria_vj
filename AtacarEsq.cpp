#include "AtacarEsq.h"
#include "EstarEsq.h"
#include <iostream>

const float AtacarEsq::velocidad = 1.0f;
#define FALL_STEP 4.0f;

AtacarEsq::AtacarEsq(Player* p, glm::ivec2* posEsq, const glm::ivec2& tMD, Sprite* sp, TileMap* m) :EstadoEsq(p, posEsq, tMD, sp, m) {
	direccionX = 0.0f;
}

EstadoEsq* AtacarEsq::cambiarEstado() {
	if (!jugadorCerca()) return new EstarEsq(player, posEsq, tileMapDisplay, spEsq, map);
	else {
		direccion();
		if (direccionX < 0) {
			glm::ivec2 nuevaPos = glm::ivec2(posEsq->x - 1.0f, posEsq->y);
			if (!map->inbounds(nuevaPos)) return new EstarEsq(player, posEsq, tileMapDisplay, spEsq, map);
			else if (map->collisionMoveLeft(glm::vec2(posEsq->x - 1.0f,
				posEsq->y), glm::vec2(32.0f, 32.0f))) return new EstarEsq(player, posEsq, tileMapDisplay, spEsq, map);
		}
		else if (direccionX > 0) {
			glm::ivec2 nuevaPos = glm::ivec2(posEsq->x + 1.0f, posEsq->y);
			if (!map->inbounds(nuevaPos)) return new EstarEsq(player, posEsq, tileMapDisplay, spEsq, map);
			if (map->collisionMoveRight
			(glm::vec2(posEsq->x + 1.0f, posEsq->y), glm::vec2(32.0f, 32.0f))) return new EstarEsq(player, posEsq, tileMapDisplay, spEsq, map);
		}
	}
	return this;
}

void AtacarEsq::update(int deltaTime) {
	perseguir(deltaTime);
}

void AtacarEsq::perseguir(int deltaTime) {
	glm::vec2 posP = player->getPosition();//Coordenadas reales
	direccion();
	float nuevaX = posEsq->x + velocidad*ceil(float(deltaTime) / 1000.0f)*direccionX;
	if (direccionX < 0 && !map->collisionMoveLeft(glm::vec2(nuevaX, posEsq->y), glm::vec2(32.0f, 32.0f)) || (direccionX > 0 && !map->collisionMoveRight(glm::vec2(nuevaX, posEsq->y), glm::vec2(32.0f, 32.0f)))) {
		posEsq->x = nuevaX;
	}
	float posYAnt = posEsq->y;
	posEsq->y += FALL_STEP;
	if (map->inbounds(glm::vec2(posEsq->x, posEsq->y))) {
		if (map->collisionMoveDown(*posEsq, glm::ivec2(32, 32), &(posEsq->y))) {
			posEsq->y = posYAnt;
		}
	}
	else posEsq->y = posYAnt;
	spEsq->setPosition(glm::vec2(float(tileMapDisplay.x + posEsq->x), float(tileMapDisplay.y + posEsq->y)));
}

void AtacarEsq::direccion() {
	//valor de threshold para que no haga movimiento intervalico
	if (abs(player->getPosition().x - posEsq->x) < 2.0f) direccionX = 0;
	else {
		if (player->getPosition().x - posEsq->x < 0) direccionX = -1;
		else if (player->getPosition().x - posEsq->x > 0) direccionX = 1;
		else direccionX = 0;
	}
	/*direccionX = ;
	if (direccionX != 0) direccionX /= abs(direccionX);*/
}
