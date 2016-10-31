#define _USE_MATH_DEFINES
#include "Atacar.h"
#include "Estar.h"
#include <iostream>
#include <cmath>

Atacar::Atacar(Scene* sc, glm::ivec2* pe,const glm::ivec2& tMD, Sprite* sp) :Estado(sc, pe,tMD, sp) {
	tocado = false;
}

Estado* Atacar::cambiarEstado() {
	if (escena->getPlayerPos().x > getCoordsRealesEnem().x) {
		std::cout << "paso a estar" << std::endl;
		return new Estar(escena, posEnemigo,tileMapDisplay, spEnem);
	}
	return this;
}

void Atacar::update(int deltaTime) {
	if (ataquesRealizados < numAtaques) { 
		hacerAtaque(deltaTime);
	}
}
//TODO: poner direccion de ataque
void Atacar::hacerAtaque(int deltaTime) {
	glm::vec2 posP = escena->getPlayerPos();
	if (velocidad.x == 0 && velocidad.y == 0) {//Comienzo embestida
		if (tocado) ++ataquesRealizados;//Si he frenado
		posPlayerAnterior = posP;
		posEnemigoAnterior = *posEnemigo;
		++velocidad.x;++velocidad.y;
		float deltaX = posP.x - posEnemigo->x; double deltaY = double(posP.y - posEnemigo->y);
		angulo = (deltaY / deltaX)*M_PI/180.0;
	}
	else {//Si en medio de embestida
		if (!tocado) { ++velocidad.x; ++velocidad.y; }
		else { --velocidad.x; --velocidad.y; }
	}
	posEnemigo->x = posEnemigo->x + velocidad.x*float(deltaTime)*float(cos(angulo));
	posEnemigo->y = posEnemigo->y + velocidad.y*float(deltaTime)*float(sin(angulo));
	tocado = distanciaActualVsDistanciaAnterior(posP);
	spEnem->setPosition(glm::vec2(float(tileMapDisplay.x + posEnemigo->x), float(tileMapDisplay.y + posEnemigo->y)));
}

bool Atacar::distanciaActualVsDistanciaAnterior(const glm::vec2 posP) {
	return ((posPlayerAnterior.x - posEnemigoAnterior.x)*(posPlayerAnterior.x - posEnemigoAnterior.x) + 
		(posPlayerAnterior.y - posEnemigoAnterior.y)*(posPlayerAnterior.y - posEnemigoAnterior.y)) <= 
		((posPlayerAnterior.x - posEnemigo->x)*(posPlayerAnterior.x - posEnemigo->x) +
		(posPlayerAnterior.y - posEnemigo->y)*(posPlayerAnterior.y - posEnemigo->y));
}