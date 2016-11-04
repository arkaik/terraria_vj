#include "Atacar.h"
#include "Estar.h"
#include <iostream>

Atacar::Atacar(Scene* sc, glm::ivec2* pe,const glm::ivec2& tMD, Sprite* sp, int* vida) :Estado(sc, pe,tMD, sp, vida) {
	tocado = false;
	ataquesRealizados = 0;
	velocidad = velocidadFuria = 0;
	furioso = false;
}

Estado* Atacar::cambiarEstado() {
	if (ataquesRealizados == numAtaques) return new Estar(escena, posEnemigo, tileMapDisplay, spEnem, vidaEn);
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
	if (!furioso) {
		if (velocidad <= 0) {//Comienzo embestida
			if (tocado) {
				++ataquesRealizados;
				tocado = false;
			}
			posPlayerAnterior = posP;
			posEnemigoAnterior = glm::vec2(posEnemigo->x, posEnemigo->y);
			++velocidad;
			direccion.x = posP.x - posEnemigo->x; direccion.y = posP.y - posEnemigo->y;
			float hyp = sqrt(direccion.x*direccion.x + direccion.y*direccion.y);
			direccion.x /= hyp;
			direccion.y /= hyp;
		}
		else {//Si en medio de embestida
			if (!tocado) { velocidad += 10; }
			else { velocidad -= 15; }
		}
		posEnemigo->x = posEnemigo->x + velocidad*float(deltaTime) / 1000.f*direccion.x;
		posEnemigo->y = posEnemigo->y + velocidad*float(deltaTime) / 1000.f*direccion.y;
		if (!tocado) tocado = distanciaActualVsDistanciaAnterior(posP);
		spEnem->setPosition(glm::vec2(float(tileMapDisplay.x + posEnemigo->x), float(tileMapDisplay.y + posEnemigo->y)));
	}
	else {
		if (velocidadFuria <= 0) {//Comienzo embestida
			if (tocado) {
				++ataquesRealizados;
				tocado = false;
			}
			posPlayerAnterior = posP;
			posEnemigoAnterior = glm::vec2(posEnemigo->x, posEnemigo->y);
			velocidad = 1;
			direccion.x = posP.x - posEnemigo->x; direccion.y = posP.y - posEnemigo->y;
			float hyp = sqrt(direccion.x*direccion.x + direccion.y*direccion.y);
			if (hyp != 0) {
				direccion.x /= hyp;
				direccion.y /= hyp;
			}
			else direccion.x = direccion.y = 0;
		}
		else {//Si en medio de embestida
			if (!tocado) { velocidadFuria += 15; }
			else { velocidadFuria -= 25; }
		}
		posEnemigo->x = posEnemigo->x + velocidadFuria*float(deltaTime) / 1000.f*direccion.x;
		posEnemigo->y = posEnemigo->y + velocidadFuria*float(deltaTime) / 1000.f*direccion.y;
		if (!tocado) tocado = distanciaActualVsDistanciaAnterior(posP);
		spEnem->setPosition(glm::vec2(float(tileMapDisplay.x + posEnemigo->x), float(tileMapDisplay.y + posEnemigo->y)));
	}
}

bool Atacar::distanciaActualVsDistanciaAnterior(const glm::vec2 posP) {
	return ((posPlayerAnterior.x - posEnemigoAnterior.x)*(posPlayerAnterior.x - posEnemigoAnterior.x) + 
		(posPlayerAnterior.y - posEnemigoAnterior.y)*(posPlayerAnterior.y - posEnemigoAnterior.y)) <= 
		((posEnemigoAnterior.x - posEnemigo->x)*(posEnemigoAnterior.x - posEnemigo->x) +
		(posEnemigoAnterior.y - posEnemigo->y)*(posEnemigoAnterior.y - posEnemigo->y));
}