#include "EstarEsq.h"
#include "AtacarEsq.h"
#include <iostream>

const float EstarEsq::distanciaRecorrido = 5.0f;

EstarEsq::EstarEsq(Player* p, glm::ivec2* pe, const glm::ivec2& tMD, Sprite* sp, TileMap* m) :EstadoEsq(p, pe, tMD, sp, m) {
	posInicial = glm::vec2(pe->x, pe->y);
	bool choque = false;
	for (int i = posInicial.x; !choque && i < posInicial.x + distanciaRecorrido; ++i) {
		if (!map->inbounds(glm::ivec2(i, posEsq->y))) {
			posInicial.x -= posInicial.x + distanciaRecorrido - i;
			choque = true;
		}
		else {
			if (map->collisionMoveRight(glm::ivec2(i, posInicial.y), glm::ivec2(32, 32))) {
				posInicial.x -= posInicial.x + distanciaRecorrido - i;
				choque = true;
			}
		}
	}
	for (int i = posInicial.x; !choque && i > posInicial.x - distanciaRecorrido; --i) {
		if (!map->inbounds(glm::ivec2(i, posEsq->y))) {
			posInicial.x += i - posInicial.x - distanciaRecorrido;
			choque = true;
		}
		else {
			if (map->collisionMoveLeft(glm::ivec2(i, posInicial.y), glm::ivec2(32, 32))) {
				posInicial.x += i - posInicial.x - distanciaRecorrido;
				choque = true;
			}
		}
	}
	bool haciaIzq = true;
}

EstadoEsq* EstarEsq::cambiarEstado() {
	if (jugadorCerca()) {
		std::cout << "Esqueletillo cambio a atacar" << std::endl;
		return new AtacarEsq(player, posEsq, tileMapDisplay, spEsq, map);
	}
	return this;
}

void EstarEsq::update(int deltaTime) {
	//optimizacion
	//int nuevaPos = (haciaIzq) ? posInicial.x - 2.0f : posInicial.x + 2.0f;
	if (haciaIzq) {
		float nuevaPos = posInicial.x - 2.0f;
		//TODO: Comprobar si estoy dentro de los limites del mapa
		if (nuevaPos < posInicial.x - distanciaRecorrido) {
			haciaIzq = false;
		}
		else {
			if (map->collisionMoveLeft(glm::vec2(nuevaPos,posEsq->y), glm::vec2(32, 32))) {
				posEsq->x = posEsq->x + 2.0f;
				haciaIzq = false;
			}
		}
	}
	else {
		float nuevaPos = posInicial.x + 2.0f;
		if (map->inbounds(glm::ivec2(nuevaPos,posEsq->y))) {

		}
		if (posInicial.x + distanciaRecorrido < nuevaPos) {
			haciaIzq = true;
		}
		else {
			if (map->collisionMoveRight(glm::vec2(nuevaPos, posEsq->y), glm::vec2(32, 32))) {
				posEsq->x = posEsq->x - 2.0f;
				haciaIzq = true;
			}
		}
	}
	spEsq->setPosition(glm::vec2(float(tileMapDisplay.x + posEsq->x), float(tileMapDisplay.y + posEsq->y)));
}