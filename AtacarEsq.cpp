#include "AtacarEsq.h"
#include "EstarEsq.h"
#include <iostream>

AtacarEsq::AtacarEsq(glm::vec2* posPlayer, glm::ivec2* posEsq, const glm::ivec2& tMD, Sprite* sp, TileMap* m) :EstadoEsq(posPlayer, posEsq, tMD, sp, m) {
	tocado = false;
	ataquesRealizados = 0;
	velocidad = 0;
}

EstadoEsq* AtacarEsq::cambiarEstado() {
	if (ataquesRealizados == numAtaques) return new EstarEsq(posPlayer, posEsq, tileMapDisplay, spEsq, map); 
	return this;
}

void AtacarEsq::update(int deltaTime) {
	if (ataquesRealizados < numAtaques) {
		hacerAtaque(deltaTime);
	}
}

void AtacarEsq::hacerAtaque(int deltaTime) {
	glm::vec2 posP = glm::vec2(posPlayer->x + float(tileMapDisplay.x), posPlayer->y + float(tileMapDisplay.y));//Coordenadas reales
	//posP.x -= tileMapDisplay.x; posP.y -= tileMapDisplay.y;//Coordenadas de player
	if (velocidad <= 0) {//Comienzo embestida
		if (tocado) {
			++ataquesRealizados;
			tocado = false;
		}
		posPlayerAnterior = posP;
		posEnemigoAnterior = glm::vec2(posEsq->x, posEsq->y);
		++velocidad;
		direccion.x = posP.x - posEsq->x; direccion.y = posP.y - posEsq->y;
		float hyp = sqrt(direccion.x*direccion.x + direccion.y*direccion.y);
		direccion.x /= hyp;
		direccion.y /= hyp;
	}
	else {//Si en medio de embestida
		if (!tocado) { velocidad += 15; }
		else { velocidad -= 25; }
	}
	posEsq->x = posEsq->x + velocidad*float(deltaTime) / 1000.f*direccion.x;
	posEsq->y = posEsq->y + velocidad*float(deltaTime) / 1000.f*direccion.y;
	//if (!tocado) tocado = distanciaActualVsDistanciaAnterior(posP);
	spEsq->setPosition(glm::vec2(float(tileMapDisplay.x + posEsq->x), float(tileMapDisplay.y + posEsq->y)));
}

/*bool AtacarEsq::distanciaActualVsDistanciaAnterior(const glm::vec2 posP) {
	return ((posPlayerAnterior.x - posEnemigoAnterior.x)*(posPlayerAnterior.x - posEnemigoAnterior.x) +
		(posPlayerAnterior.y - posEnemigoAnterior.y)*(posPlayerAnterior.y - posEnemigoAnterior.y)) <=
		((posEnemigoAnterior.x - posEnemigo->x)*(posEnemigoAnterior.x - posEnemigo->x) +
		(posEnemigoAnterior.y - posEnemigo->y)*(posEnemigoAnterior.y - posEnemigo->y));
}*/