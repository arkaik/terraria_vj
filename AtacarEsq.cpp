#include "AtacarEsq.h"
#include "EstarEsq.h"
#include <iostream>

const float AtacarEsq::velocidad = 5.0f;

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
	//posP.x -= tileMapDisplay.x; posP.y -= tileMapDisplay.y;//Coordenadas de player
	direccion();
	float nuevaX = posEsq->x + velocidad*float(deltaTime) / 1000.f*direccionX;
	posEsq->x = ((direccionX < 0 && !map->collisionMoveLeft(glm::vec2(nuevaX, posEsq->y), glm::vec2(32.0f, 32.0f))) ||
			(direccionX > 0 && !map->collisionMoveRight(glm::vec2(nuevaX, posEsq->y), glm::vec2(32.0f, 32.0f)))) ? nuevaX : posEsq->x;
	spEsq->setPosition(glm::vec2(float(tileMapDisplay.x + posEsq->x), float(tileMapDisplay.y + posEsq->y)));
}

void AtacarEsq::direccion() {
	direccionX = player->getPosition().x - posEsq->x;
	if (direccionX != 0) direccionX /= abs(direccionX);
}
