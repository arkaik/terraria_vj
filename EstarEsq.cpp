#include "EstarEsq.h"
#include "AtacarEsq.h"
#include <iostream>

const float EstarEsq::radioDeteccionPlayer = 10.0f;
const float EstarEsq::distanciaRecorrido = 5.0f;

EstarEsq::EstarEsq(glm::vec2* posP, glm::ivec2* pe, const glm::ivec2& tMD, Sprite* sp, TileMap* m) :EstadoEsq(posP, pe, tMD, sp, m) {
	posInicial = glm::vec2(pe->x, pe->y);
	bool haciaIzq = true;
}

EstadoEsq* EstarEsq::cambiarEstado() {
	if (jugadorCerca()) {
		std::cout << "Esqueletillo cambio a atacar" << std::endl;
		return new AtacarEsq(posPlayer, posEsq, tileMapDisplay, spEsq, map);
	}
	return this;
}

bool EstarEsq::jugadorCerca() {
	//x+y = rdp es la circumferencia si x^2+y^2 <= rdp^2 esta dentro sino fuera
	glm::vec2 posP = glm::vec2(posPlayer->x + float(tileMapDisplay.x), posPlayer->y + float(tileMapDisplay.y));//Coordenadas reales;
	glm::vec2 posE = glm::vec2(posEsq->x + float(tileMapDisplay.x), posEsq->y + float(tileMapDisplay.y));//Coordenadas reales;;
	glm::vec2 pp = glm::vec2(posP.x - posE.x, posP.y - posE.y);
	return pp.x*pp.x + pp.y*pp.y <= radioDeteccionPlayer*radioDeteccionPlayer;
}

void EstarEsq::update(int deltaTime) {
	if (haciaIzq) {
		posEsq->x = posInicial.x + 2.0f;
	}
	else {

	}
	/*posEsq->x = posInicial.x + x;
	posEsq->y = posInicial.y + y;
	spEsq->setPosition(glm::vec2(float(tileMapDisplay.x + posEsq->x), float(tileMapDisplay.y + posEsq->y)));
	angulo += 3.0f;
	if (angulo == 360.0f) {
		angulo = 0.0f;
		++numVueltas;
		if (numVueltas > numCiclos) numVueltas = numCiclos;//Para que lo detecte el cambio de estado
	}*/
}