#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include "Estar.h"
#include "Atacar.h"
#include "Enemigo.h"
#include <iostream>

Estar::Estar(Scene* sc,glm::ivec2* pe, const glm::ivec2& tMD, Sprite* sp):Estado(sc, pe,tMD, sp) {
	numVueltas = 0;
	angulo = 0.0f;
	posInicial = glm::vec2(pe->x,pe->y);
}

Estado* Estar::cambiarEstado() {
	if (numVueltas == numCiclos && jugadorCerca()) {
		std::cout << "cambio a atacar" << std::endl;
		return new Atacar(escena, posEnemigo,tileMapDisplay,spEnem);
	}
	return this;
}

bool Estar::jugadorCerca() {
	int rdp = escena->radioDeteccionPlayer;
	//x+y = rdp es la circumferencia si x^2+y^2 <= rdp^2 esta dentro sino fuera
	glm::vec2 posP = escena->getPlayerPos();
	glm::vec2 posEnem = getCoordsRealesEnem();
	glm::vec2 pp = glm::vec2(posP.x - posEnem.x, posP.y - posEnem.y);
	return pp.x*pp.x + pp.y*pp.y <= rdp*rdp;
}

void Estar::update(int deltaTime) {
	float rad = angulo*M_PI / 180.0f;
	float x = (float(distanciaCentro) * sqrt(2) * cos(rad)) / (sin(rad)*sin(rad) + 1);
	float y = (float(distanciaCentro) * sqrt(2) * cos(rad)* sin(rad)) / (sin(rad)*sin(rad) + 1);
	posEnemigo->x = posInicial.x + x;
	posEnemigo->y = posInicial.y + y;
	spEnem->setPosition(glm::vec2(float(tileMapDisplay.x + posEnemigo->x), float(tileMapDisplay.y + posEnemigo->y)));
	angulo += 3.0f;
	if (angulo == 360.0f) {
		angulo = 0.0f;
		++numVueltas;
		if (numVueltas > numCiclos) numVueltas = numCiclos;//Para que lo detecte el cambio de estado
	}
}