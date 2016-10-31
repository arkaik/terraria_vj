#include "Atacar.h"
#include "Estar.h"
#include <iostream>

Atacar::Atacar(Scene* sc, glm::ivec2* pe,const glm::ivec2& tMD, Sprite* sp) :Estado(sc, pe,tMD, sp) {
	tocado = false;
	ataquesRealizados = 0;
	velocidad = 0;
}

Estado* Atacar::cambiarEstado() {
	if (ataquesRealizados == numAtaques) return new Estar(escena, posEnemigo, tileMapDisplay, spEnem);
	return this;
}

void Atacar::update(int deltaTime) {
	if (ataquesRealizados < numAtaques) { 
		hacerAtaque(deltaTime);
	}
}

void Atacar::hacerAtaque(int deltaTime) {
	glm::vec2 posP = escena->getPlayerPos();//Coordenadas reales
	//posP.x -= tileMapDisplay.x; posP.y -= tileMapDisplay.y;//Coordenadas de player
	if (velocidad <= 0) {//Comienzo embestida
		if (tocado) {
			++ataquesRealizados;
			tocado = false;
		}
		posPlayerAnterior = posP;
		posEnemigoAnterior = *posEnemigo;
		++velocidad;
		direccion.x = posP.x - posEnemigo->x; direccion.y = posP.y - posEnemigo->y;
		float hyp = sqrt(direccion.x*direccion.x + direccion.y*direccion.y);
		direccion.x /= hyp;
		direccion.y /= hyp;
	}
	else {//Si en medio de embestida
		if (!tocado) { velocidad += 10; }
		else {velocidad -= 14;}
	}
	posEnemigo->x = posEnemigo->x + velocidad*float(deltaTime) / 1000.f*direccion.x;
	posEnemigo->y = posEnemigo->y + velocidad*float(deltaTime) / 1000.f*direccion.y;
	if (!tocado) tocado = distanciaActualVsDistanciaAnterior(posP);
	spEnem->setPosition(glm::vec2(float(tileMapDisplay.x + posEnemigo->x), float(tileMapDisplay.y + posEnemigo->y)));
}

bool Atacar::distanciaActualVsDistanciaAnterior(const glm::vec2 posP) {
	return ((posPlayerAnterior.x - posEnemigoAnterior.x)*(posPlayerAnterior.x - posEnemigoAnterior.x) + 
		(posPlayerAnterior.y - posEnemigoAnterior.y)*(posPlayerAnterior.y - posEnemigoAnterior.y)) <= 
		((posEnemigoAnterior.x - posEnemigo->x)*(posEnemigoAnterior.x - posEnemigo->x) +
		(posEnemigoAnterior.y - posEnemigo->y)*(posEnemigoAnterior.y - posEnemigo->y));
}